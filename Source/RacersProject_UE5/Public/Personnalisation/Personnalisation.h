#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Personnalisation.generated.h"

class ASauvegardePersonnalisation;
class AHoverControllerShowRoom;
class UTextBlock;
class UButtonAvailableMesh;
class UPlayerSpacecraft;
class UVerticalBox;
class UBackgroundBlur;
class UDataAssetSpacecraft;

UCLASS()
class RACERSPROJECT_UE5_API APersonnalisation : public AActor
{
	GENERATED_BODY()
	
public:	
	APersonnalisation();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void ArrowLeft();

	UFUNCTION(BlueprintCallable)
	void ArrowRight();

	UFUNCTION(BlueprintCallable)
	void SetupAttachmentToHoverShowRoom();

	int Index = 0;
	int MaxIndex;
	bool ShowOriginalSpacecraft = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UDataAssetSpacecraft*> DataAssetSpacecrafts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerDataAssetSpacecrafts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UPlayerSpacecraft* PlayerSpacecraftAsset;

	void GetValidDataAssetSpacecraft(int _Index);
	bool GetValidPlayerSpacecraft(UStaticMesh* TargetMesh) const;
	void RemoveStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle);
	void AddStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UMaterial* ActualMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UBackgroundBlur* LockSpacecraft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	AHoverControllerShowRoom* HoverControllerShowRoom;

	UFUNCTION(BlueprintCallable)
	void CreateChildrenForDetailCustom(UVerticalBox* ListObject);

	UFUNCTION(BlueprintCallable)
	void ShowOriginalSpacecraftBtn(UTextBlock* Text);

	void ResetIsChooseSpacecraft();
	void ResetColorBtn(UButtonAvailableMesh* NewButton);

	void SetButtonGreen(FButtonStyle& ButtonStyle);
	void SetButtonRed(FButtonStyle& ButtonStyle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> BlacklistBodyRemoved;
	
	/* Clicked Part */
	UFUNCTION(BlueprintCallable, Category = "Button Delegate")
	void TriggerButtonClickedDelegate(UStaticMesh* SelectedMesh, UButtonAvailableMesh* SelectedButton);
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clicked Property", meta=(AllowPrivateAccess="true"))
	UUserWidget* CustomizationWidget;
    
	void AttachClickedEvent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UButtonAvailableMesh> NewButtonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TMap<UButtonAvailableMesh*, UStaticMesh*> ButtonsMeshes;
	
	/* Save Personnalisation Part */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Personnalisation Save", meta=(AllowPrivateAccess="true"))
	ASauvegardePersonnalisation* SauvegardePersonnalisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Personnalisation Save", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMesh*> EquipedMesh;
};
