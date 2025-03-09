#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SauvegardePersonnalisation.generated.h"

class APersonnalisation;
class UDataAssetSpacecraft;

UCLASS()
class RACERSPROJECT_UE5_API ASauvegardePersonnalisation : public AActor
{
	GENERATED_BODY()
	
public:	
	ASauvegardePersonnalisation();
	void SavePlayerMeshToFile(TArray<UStaticMesh*> MeshesSpacecraft) const;
	void SaveMaterialForMesh(UStaticMesh* Mesh, UMaterialInterface* Material) const;
	FString LoadPlayerMeshFromFile(FString OriginalMesh) const;
	int GetArrayOfSave() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void LoadMeshToTargetDataAsset(UDataAssetSpacecraft* DataAssetSpacecraft, APersonnalisation* Personnalisation);
	
	FString SaveDirectory = FPaths::ProjectDir();
	FString SaveFilePath = SaveDirectory / TEXT("SavePersonnalisation.json");
};
