#include "Personnalisation/SauvegardePersonnalisation.h"

#include "Personnalisation/Personnalisation.h"
#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

ASauvegardePersonnalisation::ASauvegardePersonnalisation()
{

}

void ASauvegardePersonnalisation::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASauvegardePersonnalisation::SavePlayerMeshToFile(TArray<UStaticMesh*> MeshesSpacecraft) const
{
    FString JsonContent;
    TArray<TSharedPtr<FJsonValue>> JsonItems;

    // Charger le contenu du fichier JSON
    if (FFileHelper::LoadFileToString(JsonContent, *SaveFilePath))
    {
        TSharedPtr<FJsonObject> RootObject;
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonContent);

        // Désérialiser le JSON
        if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
        {
            // Vérifier si le champ "StockActualMeshPlayer" existe
            if (RootObject->HasField(TEXT("StockActualMeshPlayer")))
            {
                // Récupérer les éléments existants dans le tableau "StockActualMeshPlayer"
                TArray<TSharedPtr<FJsonValue>> ExistingJsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));
                TSet<FString> ExistingMeshNames;

                // Créer un ensemble des meshes existants dans le fichier pour faciliter la comparaison
                for (const TSharedPtr<FJsonValue>& Item : ExistingJsonItems)
                {
                    TSharedPtr<FJsonObject> JsonObject = Item->AsObject();
                    FString ExistingMeshName = JsonObject->GetStringField(TEXT("Name"));
                    ExistingMeshNames.Add(ExistingMeshName);
                }

                // Comparer et ajouter les nouveaux meshes à la liste si nécessaire
                for (UStaticMesh* Mesh : MeshesSpacecraft)
                {
                    FString MeshName = Mesh->GetName();

                    // Si le mesh n'existe pas déjà dans la liste, on l'ajoute
                    if (!ExistingMeshNames.Contains(MeshName))
                    {
                        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                        JsonObject->SetStringField(TEXT("Name"), MeshName);
                        JsonItems.Add(MakeShareable(new FJsonValueObject(JsonObject)));
                    }
                }

                // Ajouter les nouveaux éléments au tableau existant
                if (JsonItems.Num() > 0)
                {
                    // Ajouter les nouveaux meshes au tableau existant
                    ExistingJsonItems.Append(JsonItems);
                    RootObject->SetArrayField(TEXT("StockActualMeshPlayer"), ExistingJsonItems);

                    // Sérialiser et sauvegarder dans le fichier
                    FString OutputString;
                    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
                    FJsonSerializer::Serialize(RootObject.ToSharedRef(), JsonWriter);

                    // Sauvegarder dans le fichier
                    FFileHelper::SaveStringToFile(OutputString, *SaveFilePath);

                    UE_LOG(LogTemp, Warning, TEXT("Fichier mis à jour avec les nouveaux meshes à %s"), *SaveFilePath);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Aucun nouveau mesh à ajouter."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Le champ 'StockActualMeshPlayer' n'existe pas dans le fichier JSON."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Erreur de désérialisation du fichier JSON."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Échec du chargement du fichier JSON."));
    }
}

FString ASauvegardePersonnalisation::LoadPlayerMeshFromFile(FString OriginalMesh) const
{
    FString FileContent;
    
    if (FFileHelper::LoadFileToString(FileContent, *SaveFilePath))
    {
        TSharedPtr<FJsonObject> RootObject;
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContent);

        if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
        {
            const TArray<TSharedPtr<FJsonValue>>& JsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));

            if (JsonItems.Num() > 0)
            {
                for (const TSharedPtr<FJsonValue>& JsonValue : JsonItems)
                {
                    TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();

                	FString MeshName = JsonObject->GetStringField(TEXT("Name"));
                    if (OriginalMesh == MeshName) return MeshName;
                }
            }
        }
    }

	return "NULL";
}

int ASauvegardePersonnalisation::GetArrayOfSave() const
{
	FString FileContent;
	if (FFileHelper::LoadFileToString(FileContent, *SaveFilePath))
	{
		TSharedPtr<FJsonObject> RootObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContent);

		if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
		{
			const TArray<TSharedPtr<FJsonValue>>& JsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));
			UE_LOG(LogTemp, Warning, TEXT("JsonItems contains : %d"), JsonItems.Num());
			
			return JsonItems.Num();
		}
	}
	return -1;
}

void ASauvegardePersonnalisation::LoadMeshToTargetDataAsset(UDataAssetSpacecraft* DataAssetSpacecraft, APersonnalisation* Personnalisation)
{
	FString FileContent;
	DataAssetSpacecraft->SpacecraftMeshes.Reset();

	if (FFileHelper::LoadFileToString(FileContent, *SaveFilePath))
	{
		TSharedPtr<FJsonObject> RootObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContent);

		if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
		{
			const TArray<TSharedPtr<FJsonValue>>& JsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));

			if (JsonItems.Num() > 0)
			{
				TMap<FString, UStaticMesh*> MeshMap;
				for (const TPair<UStaticMesh*, FVector>& Pair : DataAssetSpacecraft->OriginalSpacecraft->SpacecraftMeshes)
				{
					MeshMap.Add(Pair.Key->GetName(), Pair.Key);
				}

				for (const TSharedPtr<FJsonValue>& JsonValue : JsonItems)
				{
					FString MeshName = JsonValue->AsObject()->GetStringField(TEXT("Name"));
					if (UStaticMesh** FoundMesh = MeshMap.Find(MeshName))
					{
						DataAssetSpacecraft->SpacecraftMeshes.Add(*FoundMesh);
					}
				}

				Personnalisation->SetupAttachmentToHoverShowRoom();
			}
		}
	}
}

void ASauvegardePersonnalisation::SaveMaterialForMesh(UStaticMesh* Mesh, FString Material) const
{
	if (!Mesh || Material.IsEmpty()) return;

	FString MeshName = Mesh->GetName();

	FString JsonContent;
	if (FFileHelper::LoadFileToString(JsonContent, *SaveFilePath))
	{
		TSharedPtr<FJsonObject> RootObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonContent);

		if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
		{
			TArray<TSharedPtr<FJsonValue>> JsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));

			for (TSharedPtr<FJsonValue>& Item : JsonItems)
			{
				TSharedPtr<FJsonObject> JsonObject = Item->AsObject();
				if (JsonObject->GetStringField(TEXT("Name")) == MeshName)
				{
					JsonObject->SetStringField(TEXT("Material"), Material);
					break;
				}
			}

			RootObject->SetArrayField(TEXT("StockActualMeshPlayer"), JsonItems);

			FString OutputString;
			TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(RootObject.ToSharedRef(), JsonWriter);

			FFileHelper::SaveStringToFile(OutputString, *SaveFilePath);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Updated material for mesh: %s"), *MeshName);
}

FString ASauvegardePersonnalisation::LoadPlayerMaterialsFromFile(FString OriginalMesh) const
{
	FString FileContent;
    
	if (FFileHelper::LoadFileToString(FileContent, *SaveFilePath))
	{
		TSharedPtr<FJsonObject> RootObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContent);

		if (FJsonSerializer::Deserialize(JsonReader, RootObject) && RootObject.IsValid())
		{
			const TArray<TSharedPtr<FJsonValue>>& JsonItems = RootObject->GetArrayField(TEXT("StockActualMeshPlayer"));

			if (JsonItems.Num() > 0)
			{
				for (const TSharedPtr<FJsonValue>& JsonValue : JsonItems)
				{
					TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();

					FString MeshName = JsonObject->GetStringField(TEXT("Name"));
					FString MaterialName = JsonObject->GetStringField(TEXT("Material"));
					if (OriginalMesh == MeshName) return MaterialName;
				}
			}
		}
	}

	return "NULL";
}