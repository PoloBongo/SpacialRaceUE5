#include "Personnalisation/SauvegardePersonnalisation.h"

ASauvegardePersonnalisation::ASauvegardePersonnalisation()
{

}

void ASauvegardePersonnalisation::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASauvegardePersonnalisation::SavePlayerMeshToFile(TArray<UStaticMesh*> MeshesSpacecraft)
{
	TArray<TSharedPtr<FJsonValue>> JsonItems;

	for (UStaticMesh* Mesh : MeshesSpacecraft)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetStringField(TEXT("Name"), Mesh->GetName());
		JsonItems.Add(MakeShareable(new FJsonValueObject(JsonObject)));
	}
	TSharedPtr<FJsonObject> RootObject = MakeShareable(new FJsonObject());
	RootObject->SetArrayField(TEXT("StockActualMeshPlayer"), JsonItems);

	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(RootObject.ToSharedRef(), JsonWriter);
	
	FFileHelper::SaveStringToFile(OutputString, *SaveFilePath);
	
	UE_LOG(LogTemp, Warning, TEXT("Save File Path: %s"), *SaveFilePath);
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
