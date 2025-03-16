#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Personnalisation.generated.h"

class AGameNotificationManager;
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

	/* Permet d'attacher les meshes de la save au hover controller */
	void SetupAttachmentToHoverShowRoom() const;

protected:
	virtual void BeginPlay() override;

private:
	/* Permet de naviguer à gauche */
	UFUNCTION(BlueprintCallable)
	void ArrowLeft();

	/* Permet de naviguer à droite */
	UFUNCTION(BlueprintCallable)
	void ArrowRight();
	
	int Index = 0;
	int MaxIndex;
	bool ShowOriginalSpacecraft = false;

	/* Listes de tous DataAsset des hovers*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UDataAssetSpacecraft*> DataAssetSpacecrafts;

	/* Référence au DataAsset du player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UDataAssetSpacecraft* PlayerDataAssetSpacecrafts;

	/* Référence par default ( au début du jeu ) au DataAsset du player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UPlayerSpacecraft* PlayerSpacecraftAsset;

	void GetValidDataAssetSpacecraft(int _Index);
	bool GetValidPlayerSpacecraft(UStaticMesh* TargetMesh) const;
	void RemoveStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle);
	void AddStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle);
	void SwitchMaterialFromPlayerSpacecraft(UStaticMesh* TargetMesh, UMaterial* TargetMaterial) const;

	/* Permet de récupérer par default l'actuel matériel du player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UMaterial* ActualMaterial;

	/* Liste de tous les materiels disponible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UMaterial*> AllAvailableMaterials;

	/* Background flou pour les hovers non débloqué */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UBackgroundBlur* LockSpacecraft;

	/* Référence au hover controller du player en mode show room */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	AHoverControllerShowRoom* HoverControllerShowRoom;

	/* fonction permettant de créer tous les boutons et menus déroulants pour chaque maillage et couleur */
	UFUNCTION(BlueprintCallable)
	void CreateChildrenForDetailCustom(UVerticalBox* ListObject);

	/* fonction permettant d'afficher le vaisseau spatial original avec toutes les possibilités de maillage */
	UFUNCTION(BlueprintCallable)
	void ShowOriginalSpacecraftBtn(UTextBlock* Text);

	void ResetIsChooseSpacecraft();

	/* Bouton de couleur Rouge/Vert Par défaut = Rouge */
	void ResetColorBtn(UButtonAvailableMesh* NewButton);
	void SetButtonGreen(FButtonStyle& ButtonStyle);
	void SetButtonRed(FButtonStyle& ButtonStyle);

	/* Liste des meshes que le player ne peut pas retirer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> BlacklistBodyRemoved;

	/* Liste des engines (mesh) disponible sur le hover pour que le player ne puisse pas en équiper plus de deux */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> ListEngines;

	/* Liste des cockpit (mesh) disponible sur le hover pour que le player ne puisse pas en équiper plus de deux */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<FString> ListCockpits;

	bool CheckOneEngineOnSpaceCraft(const UStaticMesh* TargetMesh) const;
	bool CheckOneCockPitOnSpaceCraft(const UStaticMesh* TargetMesh) const;

	/* Selection Changed Part */
	UFUNCTION(BlueprintCallable, Category = "Button Delegate")
	void TriggerSelectionChangedDelegate(FString SelectionItem = "M_Vortex_Yellow", UStaticMesh* SelectedMesh = nullptr);

	/* Référence à la classe pour le dopdown custom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UPersonnalisationComboBoxString> NewComboBoxClass;

	/*  Map pour associé chaque dropdown à un static mesh affiché */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TMap<UPersonnalisationComboBoxString*, UStaticMesh*> ComboBoxStringArray;

	void AttachSelectionChangedEvent() const;
	UPersonnalisationComboBoxString* NewComboBoxString = nullptr;

	/* Permet d'attacher les materiels de chaque partie du hover correspondante */
	UFUNCTION(BlueprintCallable)
	FString SetupAttachmentMaterialToHoverShowRoom(UStaticMesh* StaticMesh) const;
	
	/* Clicked Part */
	UFUNCTION(BlueprintCallable, Category = "Button Delegate")
	void TriggerButtonClickedDelegate(UStaticMesh* SelectedMesh, UButtonAvailableMesh* SelectedButton);

	/* Référence au widget de personnalisation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clicked Property", meta=(AllowPrivateAccess="true"))
	UUserWidget* CustomizationWidget;
    
	void AttachClickedEvent() const;

	/* Réf a la classe Button pour l'instancier*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UButtonAvailableMesh> NewButtonClass;

	/* Permet d'associé chaque boutton à un static mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TMap<UButtonAvailableMesh*, UStaticMesh*> ButtonsMeshes;
	
	/* Save Personnalisation Part */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Personnalisation Save", meta=(AllowPrivateAccess="true"))
	ASauvegardePersonnalisation* SauvegardePersonnalisation;

	/* Stock les meshes déjà équippé */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Personnalisation Save", meta=(AllowPrivateAccess="true"))
	TArray<UStaticMesh*> EquipedMesh;

	/* Button to show/hidde when spacecraft switch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(AllowPrivateAccess="true"))
	TArray<UButton*> Buttons;

	void ManageVisibilitiesButtons(bool IsVisible);

	UFUNCTION(BlueprintCallable)
	void SetupPosForEachMeshPart();

	/* Notification Part */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Notification", meta=(AllowPrivateAccess="true"))
	AGameNotificationManager* GameNotificationManager;
	
};
