#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SauvegardePersonnalisation.generated.h"

UCLASS()
class RACERSPROJECT_UE5_API ASauvegardePersonnalisation : public AActor
{
	GENERATED_BODY()
	
public:	
	ASauvegardePersonnalisation();
	void SavePlayerMeshToFile(TArray<UStaticMesh*> MeshesSpacecraft);
	FString LoadPlayerMeshFromFile(FString OriginalMesh) const;
	int GetArrayOfSave() const;

protected:
	virtual void BeginPlay() override;

private:
	FString SaveDirectory = FPaths::ProjectDir();
	FString SaveFilePath = SaveDirectory / TEXT("SavePersonnalisation.json");
};
