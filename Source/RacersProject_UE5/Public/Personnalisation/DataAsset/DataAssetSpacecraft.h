#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetSpacecraft.generated.h"

/**
 * 
 */
UCLASS()
class RACERSPROJECT_UE5_API UDataAssetSpacecraft : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	UMaterial* Material;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TArray<UStaticMesh*> SpacecraftMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	bool Unlock;
};
