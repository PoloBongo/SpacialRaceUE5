#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoverControllerShowRoom.generated.h"

class UDataAssetSpacecraft;

UCLASS()
class RACERSPROJECT_UE5_API AHoverControllerShowRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	AHoverControllerShowRoom();

	void SetupMeshComponents(UStaticMesh* TargetMesh);
	void DetachMeshComponents(UStaticMesh* TargetMesh);
	void SetupMaterialToTargetMesh(UStaticMesh* TargetMesh, UMaterial* TargetMaterial) const;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MainComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMeshComponent*> MeshComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerDataAssetSpacecrafts;
};
