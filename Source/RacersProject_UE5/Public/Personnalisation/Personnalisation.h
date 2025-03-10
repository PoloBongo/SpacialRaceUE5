#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Personnalisation.generated.h"

class UPersonnalisationComboBoxString;
class UButton;
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

	void SetupAttachmentToHoverShowRoom() const;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void ArrowLeft();

	UFUNCTION(BlueprintCallable)
	void ArrowRight();
	
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
	void SwitchMaterialFromPlayerSpacecraft(UStaticMesh* TargetMesh, UMaterial* TargetMaterial) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UMaterial* ActualMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UMaterial*> AllAvailableMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UBackgroundBlur* LockSpacecraft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	AHoverControllerShowRoom* HoverControllerShowRoom;

	/* Function to create all buttons and dropdown for each mesh and color */
	UFUNCTION(BlueprintCallable)
	void CreateChildrenForDetailCustom(UVerticalBox* ListObject);

	/* Function to show Original Spacecraft with all meshes possibilities */
	UFUNCTION(BlueprintCallable)
	void ShowOriginalSpacecraftBtn(UTextBlock* Text);

	void ResetIsChooseSpacecraft();

	/* Color Button Red/Green Default = Red */
	void ResetColorBtn(UButtonAvailableMesh* NewButton);
	void SetButtonGreen(FButtonStyle& ButtonStyle);
	void SetButtonRed(FButtonStyle& ButtonStyle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> BlacklistBodyRemoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> ListEngines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> ListCockpits;

	bool CheckOneEngineOnSpaceCraft(const UStaticMesh* TargetMesh) const;
	bool CheckOneCockPitOnSpaceCraft(const UStaticMesh* TargetMesh) const;

	/* Selection Changed Part */
	UFUNCTION(BlueprintCallable, Category = "Button Delegate")
	void TriggerSelectionChangedDelegate(FString SelectionItem = "M_Vortex_Yellow", UStaticMesh* SelectedMesh = nullptr);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UPersonnalisationComboBoxString> NewComboBoxClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TMap<UPersonnalisationComboBoxString*, UStaticMesh*> ComboBoxStringArray;

	void AttachSelectionChangedEvent() const;
	UPersonnalisationComboBoxString* NewComboBoxString = nullptr;

	UFUNCTION(BlueprintCallable)
	FString SetupAttachmentMaterialToHoverShowRoom(UStaticMesh* StaticMesh) const;
	
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

	/* Button to show/hidde when spacecraft switch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(AllowPrivateAccess="true"))
	TArray<UButton*> Buttons;

	void ManageVisibilitiesButtons(bool IsVisible);

	UFUNCTION(BlueprintCallable)
	void SetupPosForEachMeshPart();
};
