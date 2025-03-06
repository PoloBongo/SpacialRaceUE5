#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverController.generated.h"

class UDataAssetSpacecraft;

UCLASS()
class RACERSPROJECT_UE5_API AHoverController : public APawn
{
	GENERATED_BODY()

public:
	AHoverController();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMeshComponent*> MeshesComponents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerSpacecraft;

	int Length = 11;
};
