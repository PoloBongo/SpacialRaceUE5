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
	AHoverController(int _Length);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetLengthSpacecraftMesh(int _Length);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
	void SetupInput();

	void Initialize(int _Length);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMeshComponent*> MeshesComponents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerSpacecraft;

	void SetupVariable();

	int LengthSpacecraftMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float BoostMultiplier = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float AngularRotSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float ThrustSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float SpinImpulseTopForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float SpinReverseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta=(AllowPrivateAccess="true"))
	float LateralForceReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta=(AllowPrivateAccess="true"))
	float SpeedToForceFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta=(AllowPrivateAccess="true"))
	float AngularSpeedToForceFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta=(AllowPrivateAccess="true"))
	float Damping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta=(AllowPrivateAccess="true"))
	float Stifness;
	
	virtual void SetupInput_Implementation();
};
