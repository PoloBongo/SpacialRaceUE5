#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerSpacecraft.generated.h"

/**
 * 
 */
UCLASS()
class RACERSPROJECT_UE5_API UPlayerSpacecraft : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	UMaterial* Material;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TArray<UStaticMesh*> ActualPlayerMeshes;
};
