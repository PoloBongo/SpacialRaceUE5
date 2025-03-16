#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerSpacecraft.generated.h"

/* Hover par default au commencement du jeu ( quand la save n'est pas chargé ou qu'elle est vide ) */
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
