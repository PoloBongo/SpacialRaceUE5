#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverController.generated.h"

class UPossibilityDataCombinaison;
class UDataAssetSpacecraft;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class RACERSPROJECT_UE5_API AHoverController : public APawn
{
	GENERATED_BODY()

public:
	AHoverController(const FObjectInitializer& ObjectInitializer);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetLengthSpacecraftMesh(int _Length);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
	void SetupInput();

	void Initialize(int _Length);

private:
	/* Liste des combinaisons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combinaison", meta=(AllowPrivateAccess="true"))
	TArray<UPossibilityDataCombinaison*> PossibilityDataCombinaison;

	/* Listes des mesh components créer selon le nombre de partie séléctionner par le joueur */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMeshComponent*> MeshesComponents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerSpacecraft;

	void SetupVariable();
	void SetupAttachmentMeshToHover();
	void SetupNiagaraEngine(const FString& StaticMeshName);

	/* Permet de récupérer de DataAsset chaque niagara à son transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TMap<UNiagaraSystem*, FTransform> EnginesNiagara;

	/* Réf au niagara pour l'engine actuel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UNiagaraComponent* ActualEngineNiagara;

	/* Référence au data pour la physique, permet de les appliquer au Hover Controller */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
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
