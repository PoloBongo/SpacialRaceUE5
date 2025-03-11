#include "Personnalisation/Personnalisation.h"

#include "Components/BackgroundBlur.h"
#include "Personnalisation/ButtonAvailableMesh.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Personnalisation/SauvegardePersonnalisation.h"
#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "Personnalisation/DataAsset/PlayerSpacecraft.h"
#include "Player/HoverControllerShowRoom.h"
#include "Widget/PersonnalisationComboBoxString.h"

APersonnalisation::APersonnalisation(): MaxIndex(0), PlayerDataAssetSpacecrafts(nullptr),
                                        PlayerSpacecraftAsset(nullptr), ActualMaterial(nullptr),
                                        LockSpacecraft(nullptr), HoverControllerShowRoom(nullptr),
                                        CustomizationWidget(nullptr), SauvegardePersonnalisation(nullptr)
{
}

void APersonnalisation::BeginPlay()
{
	Super::BeginPlay();
	GetValidDataAssetSpacecraft(0);
	MaxIndex = DataAssetSpacecrafts.Num() - 1;
	ManageVisibilitiesButtons(true);
}

void APersonnalisation::SetupAttachmentToHoverShowRoom() const
{
	for (const TPair<UStaticMesh*, FVector>& Pair : PlayerDataAssetSpacecrafts->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		FString NameStaticMesh = StaticMesh->GetName();

		FString TargetStaticMesh = SauvegardePersonnalisation->LoadPlayerMeshFromFile(NameStaticMesh);
		if(TargetStaticMesh == NameStaticMesh)
		{
			HoverControllerShowRoom->SetupMeshComponents(StaticMesh);
		}
	}
}

FString APersonnalisation::SetupAttachmentMaterialToHoverShowRoom(UStaticMesh* StaticMesh) const
{
	for (const TPair<UMaterial*, bool>& MatResult : PlayerDataAssetSpacecrafts->SpacecraftMaterials)
	{
		UMaterial* Material = MatResult.Key;
		FString NameMaterial = Material->GetName();

		FString TargetStaticMesh = SauvegardePersonnalisation->LoadPlayerMaterialsFromFile(*StaticMesh->GetName());
		if(TargetStaticMesh == NameMaterial)
		{
			HoverControllerShowRoom->SetupMaterialToTargetMesh(StaticMesh, Material);
			return Material->GetName();
		}
	}

	return "NULL";
}

void APersonnalisation::ArrowLeft()
{
	if (Index > 0)
	{
		Index--;
		GetValidDataAssetSpacecraft(Index);
	}
}

void APersonnalisation::ArrowRight()
{
	if (Index < MaxIndex)
	{
		Index++;
		GetValidDataAssetSpacecraft(Index);
	}
}

void APersonnalisation::GetValidDataAssetSpacecraft(int _Index)
{
	if (!LockSpacecraft) return;
	
	if (DataAssetSpacecrafts.IsValidIndex(_Index))
	{
		if (!DataAssetSpacecrafts[_Index]->Unlock)
		{
			LockSpacecraft->SetVisibility(ESlateVisibility::Visible);
			ActualMaterial = DataAssetSpacecrafts[_Index]->Material;
			ManageVisibilitiesButtons(false);
		}
		else
		{
			LockSpacecraft->SetVisibility(ESlateVisibility::Hidden);
			DataAssetSpacecrafts[_Index]->IsChoose = true;
			ActualMaterial = PlayerSpacecraftAsset->Material;
			ManageVisibilitiesButtons(true);
		}
	}
}

void APersonnalisation::ManageVisibilitiesButtons(const bool IsVisible)
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i])
		{
			Buttons[i]->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
}


void APersonnalisation::ShowOriginalSpacecraftBtn(UTextBlock* Text)
{
	ShowOriginalSpacecraft = !ShowOriginalSpacecraft;

	if (ShowOriginalSpacecraft)
	{
		ActualMaterial = DataAssetSpacecrafts[Index]->Material;
		Text->SetText(FText::FromString("Voir mon Vaisseau"));
	}
	else
	{
		ActualMaterial = PlayerSpacecraftAsset->Material;
		Text->SetText(FText::FromString("Voir l'original"));
	}
}

void APersonnalisation::ResetIsChooseSpacecraft()
{	
	for (int i = 0; i < DataAssetSpacecrafts.Num(); i++)
	{
		if (!DataAssetSpacecrafts[i]->IsChoose)
		{
			DataAssetSpacecrafts[i]->IsChoose = false;
		}
	}
}

void APersonnalisation::CreateChildrenForDetailCustom(UVerticalBox* ListObject)
{
	if (!ListObject || !NewButtonClass || !NewComboBoxClass) return;

	ButtonsMeshes.Reset();
	ComboBoxStringArray.Reset();
	ListObject->ClearChildren();
	
	if (!DataAssetSpacecrafts[Index]->IsChoose) return;

	for (const TPair<UStaticMesh*, FVector>& Pair : DataAssetSpacecrafts[Index]->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		FVector SpawnPos = Pair.Value;

		if (!StaticMesh) return;

		FString MeshName = StaticMesh->GetName();

		UHorizontalBox* NewHorizontalBox = NewObject<UHorizontalBox>(ListObject);
		UButtonAvailableMesh* NewButton = NewObject<UButtonAvailableMesh>(this, NewButtonClass);
		UTextBlock* NewTextBlock = NewObject<UTextBlock>(NewButton);
		NewComboBoxString = NewObject<UPersonnalisationComboBoxString>(this, NewComboBoxClass);

		NewTextBlock->SetText(FText::FromString(MeshName));

		NewButton->AddChild(NewTextBlock);
		NewHorizontalBox->AddChild(NewButton);
		NewHorizontalBox->AddChild(NewComboBoxString);
		ListObject->AddChild(NewHorizontalBox);

		ResetColorBtn(NewButton);
		NewComboBoxString->AddOption(DataAssetSpacecrafts[Index]->InitialMaterial->GetName());

		for (const TPair<UMaterial*, bool>& MaterialPair : DataAssetSpacecrafts[Index]->SpacecraftMaterials)
		{
			const UMaterial* Material = MaterialPair.Key;

			if (Material)
			{
				NewComboBoxString->AddOption(Material->GetName());
			}
		}

		FString SelectedMaterialName = SetupAttachmentMaterialToHoverShowRoom(StaticMesh);
		NewComboBoxString->SetSelectedOption(SelectedMaterialName);
		if (SelectedMaterialName == "NULL") NewComboBoxString->SetSelectedOption(DataAssetSpacecrafts[Index]->InitialMaterial->GetName());
		NewComboBoxString->RefreshOptions();

		FString TargetStaticMesh = SauvegardePersonnalisation->LoadPlayerMeshFromFile(StaticMesh->GetName());
		FButtonStyle ButtonStyle = NewButton->GetStyle();
					
		if (StaticMesh->GetName() == TargetStaticMesh)
		{
			SetButtonGreen(ButtonStyle);
			EquipedMesh.Add(StaticMesh);
			PlayerDataAssetSpacecrafts->SpacecraftMeshes[StaticMesh] = SpawnPos;
		}
		NewButton->SetStyle(ButtonStyle);
		ButtonsMeshes.Add(NewButton, StaticMesh);
		ComboBoxStringArray.Add(NewComboBoxString, StaticMesh);
		SauvegardePersonnalisation->SaveMaterialForMesh(StaticMesh, SelectedMaterialName);
	}
	SauvegardePersonnalisation->SavePlayerMeshToFile(EquipedMesh);
	AttachClickedEvent();
	AttachSelectionChangedEvent();
}

void APersonnalisation::SetupPosForEachMeshPart()
{
	for (const TPair<UStaticMesh*, FVector>& Pair : DataAssetSpacecrafts[Index]->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		FVector SpawnPos = Pair.Value;

		if (!StaticMesh) return;
		
		FString TargetStaticMesh = SauvegardePersonnalisation->LoadPlayerMeshFromFile(StaticMesh->GetName());
		if (StaticMesh->GetName() == TargetStaticMesh)
		{
			PlayerDataAssetSpacecrafts->SpacecraftMeshes[StaticMesh] = SpawnPos;
		}
	}
}


void APersonnalisation::ResetColorBtn(UButtonAvailableMesh* NewButton)
{
	FButtonStyle ButtonStyle = NewButton->GetStyle();
	SetButtonRed(ButtonStyle);
	NewButton->SetStyle(ButtonStyle);
}

void APersonnalisation::TriggerButtonClickedDelegate(UStaticMesh* SelectedMesh, UButtonAvailableMesh* SelectedButton)
{
	if (!SelectedMesh || !SelectedButton || !PlayerDataAssetSpacecrafts) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Nom : %s"), *SelectedMesh->GetName());
	FButtonStyle ButtonStyle = SelectedButton->GetStyle();
	
	if (!GetValidPlayerSpacecraft(SelectedMesh))
	{
		AddStaticMeshFromPlayerSpacecraft(SelectedMesh, ButtonStyle);
	}
	else
	{
		RemoveStaticMeshFromPlayerSpacecraft(SelectedMesh, ButtonStyle);
	}

	SelectedButton->SetStyle(ButtonStyle);
}

void APersonnalisation::AttachClickedEvent() const
{
	if (UFunction* BindingTargetButtonClickedFunction = CustomizationWidget->FindFunction(TEXT("BindingTargetButtonClicked")))
	{        
		CustomizationWidget->ProcessEvent(BindingTargetButtonClickedFunction, nullptr);
	}
}

bool APersonnalisation::GetValidPlayerSpacecraft(UStaticMesh* TargetMesh) const
{
	if (!PlayerDataAssetSpacecrafts) return false;

	return PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh);
}

void APersonnalisation::RemoveStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle)
{
	if (!PlayerDataAssetSpacecrafts) return;

	for (int i = 0; i < BlacklistBodyRemoved.Num(); i++)
	{
		if (TargetMesh->GetName() == BlacklistBodyRemoved[i]) return;
	}

	if (PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh))
	{
		PlayerDataAssetSpacecrafts->SpacecraftMeshes.Remove(TargetMesh);
		HoverControllerShowRoom->DetachMeshComponents(TargetMesh);
		SetButtonRed(ButtonStyle);
		// Save //
		if (EquipedMesh.Contains(TargetMesh))
		{
			EquipedMesh.Remove(TargetMesh);
			SauvegardePersonnalisation->SavePlayerMeshToFile(EquipedMesh);
		}
	}
}

void APersonnalisation::AddStaticMeshFromPlayerSpacecraft(UStaticMesh* TargetMesh, FButtonStyle& ButtonStyle)
{
	if (!PlayerDataAssetSpacecrafts && !HoverControllerShowRoom) return;
	
	if (!PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh) && PlayerDataAssetSpacecrafts->OriginalSpacecraft->SpacecraftMeshes.Contains(TargetMesh))
	{
		bool IsEngine = CheckOneEngineOnSpaceCraft(TargetMesh);
		bool IsCockpit = CheckOneCockPitOnSpaceCraft(TargetMesh);
		
		if (IsEngine)
		{
			for (const TPair<UStaticMesh*, FVector>& Pair : PlayerDataAssetSpacecrafts->SpacecraftMeshes)
			{
				if (ListEngines.Contains(Pair.Key->GetName()))
				{
					return;
				}
			}
		}
		
		if (IsCockpit)
		{
			for (const TPair<UStaticMesh*, FVector>& Pair : PlayerDataAssetSpacecrafts->SpacecraftMeshes)
			{
				if (ListCockpits.Contains(Pair.Key->GetName()))
				{
					return;
				}
			}
		}

		FVector DefaultLocation = PlayerDataAssetSpacecrafts->OriginalSpacecraft->SpacecraftMeshes[TargetMesh];
		
		PlayerDataAssetSpacecrafts->SpacecraftMeshes.Add(TargetMesh, DefaultLocation);
		HoverControllerShowRoom->SetupMeshComponents(TargetMesh);
		SetButtonGreen(ButtonStyle);
		// Save //
		if (!EquipedMesh.Contains(TargetMesh))
		{
			EquipedMesh.Add(TargetMesh);
			SauvegardePersonnalisation->SavePlayerMeshToFile(EquipedMesh);
		}
	}
}

bool APersonnalisation::CheckOneEngineOnSpaceCraft(const UStaticMesh* TargetMesh) const
{
	return ListEngines.Contains(TargetMesh->GetName());
}

bool APersonnalisation::CheckOneCockPitOnSpaceCraft(const UStaticMesh* TargetMesh) const
{
	return ListCockpits.Contains(TargetMesh->GetName());
}

void APersonnalisation::SetButtonGreen(FButtonStyle& ButtonStyle)
{
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor::Green);
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor::Green);
}

void APersonnalisation::SetButtonRed(FButtonStyle& ButtonStyle)
{
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Red);
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor::Red);
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor::Red);
}

void APersonnalisation::AttachSelectionChangedEvent() const
{
	if (UFunction* BindingTargetSelectionChangedFunction = CustomizationWidget->FindFunction(TEXT("BindingTargetSelectionChanged")))
	{
		CustomizationWidget->ProcessEvent(BindingTargetSelectionChangedFunction, nullptr);
	}
}

void APersonnalisation::TriggerSelectionChangedDelegate(FString SelectionItem, UStaticMesh* SelectedMesh)
{
	if (SelectionItem.IsEmpty() || !SelectedMesh || !PlayerDataAssetSpacecrafts) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Nom : %s\nNom2 : %s"), *SelectionItem, *SelectedMesh->GetName());
	
	UMaterial** FoundMaterial = AllAvailableMaterials.FindByPredicate([&](UMaterial* Mat)
	{
		return Mat && Mat->GetName() == SelectionItem;
	});

	if (FoundMaterial)
	{
		UMaterial* TargetMaterial = *FoundMaterial;
		if (TargetMaterial && GetValidPlayerSpacecraft(SelectedMesh))
		{
			SwitchMaterialFromPlayerSpacecraft(SelectedMesh, TargetMaterial);
		}
	}
}

void APersonnalisation::SwitchMaterialFromPlayerSpacecraft(UStaticMesh* TargetMesh, UMaterial* TargetMaterial) const
{
	if (!PlayerDataAssetSpacecrafts && !HoverControllerShowRoom) return;

	if (PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh))
	{
		HoverControllerShowRoom->SetupMaterialToTargetMesh(TargetMesh, TargetMaterial);
		// Save //
		SauvegardePersonnalisation->SaveMaterialForMesh(TargetMesh, TargetMaterial->GetName());
	}
}
