#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PossibilityDataCombinaison.generated.h"

/* Liste des combinaisons possible pour gérer la physique de chaque vaisseau selon son nombre de mesh */
UCLASS()
class RACERSPROJECT_UE5_API UPossibilityDataCombinaison : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	int NumbersOfMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float SpeedToForceFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float AngularSpeedToForceFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float Damping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float Stifness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float LateralForceReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float AngularRotSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float ThrustSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
	float SpinImpulseTopForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
	float SpinReverseForce;
};
