#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SauvegardePersonnalisation.generated.h"

class APersonnalisation;
class UDataAssetSpacecraft;

/* Fichier de sauvegarde pour la personnalisation du hover */
UCLASS()
class RACERSPROJECT_UE5_API ASauvegardePersonnalisation : public AActor
{
	GENERATED_BODY()
	
public:	
	ASauvegardePersonnalisation();
	void SavePlayerMeshToFile(TArray<UStaticMesh*> MeshesSpacecraft) const;
	void SaveMaterialForMesh(UStaticMesh* Mesh, FString Material) const;
	FString LoadPlayerMeshFromFile(FString OriginalMesh) const;
	FString LoadPlayerMaterialsFromFile(FString OriginalMesh) const;
	int GetArrayOfSave() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void LoadMeshToTargetDataAsset(UDataAssetSpacecraft* DataAssetSpacecraft, APersonnalisation* Personnalisation);
	
	FString SaveDirectory = FPaths::ProjectDir();
	FString SaveFilePath = SaveDirectory / TEXT("SavePersonnalisation.json");
};
