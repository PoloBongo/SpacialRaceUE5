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
	UMaterial* InitialMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TMap<UStaticMesh*, bool> SpacecraftMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TMap<UMaterial*, bool> SpacecraftMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	bool Unlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	bool IsChoose;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float SpinImpulseTopForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	float SpinReverseForce;
};
