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
}

void APersonnalisation::SetupAttachmentToHoverShowRoom()
{
	for (const TPair<UStaticMesh*, bool>& Pair : PlayerDataAssetSpacecrafts->SpacecraftMeshes)
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
		}
		else
		{
			LockSpacecraft->SetVisibility(ESlateVisibility::Hidden);
			DataAssetSpacecrafts[_Index]->IsChoose = true;
			ActualMaterial = PlayerSpacecraftAsset->Material;
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
	if (!ListObject && !NewButtonClass) return;

	ButtonsMeshes.Reset();
	ListObject->ClearChildren();
	
	if (!DataAssetSpacecrafts[Index]->IsChoose) return;

	for (const TPair<UStaticMesh*, bool>& Pair : DataAssetSpacecrafts[Index]->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;

		if (!StaticMesh) return;

		FString MeshName = StaticMesh->GetName();

		UHorizontalBox* NewHorizontalBox = NewObject<UHorizontalBox>(ListObject);
		UButtonAvailableMesh* NewButton = NewObject<UButtonAvailableMesh>(this, NewButtonClass);
		UTextBlock* NewTextBlock = NewObject<UTextBlock>(NewButton);
		UComboBoxString* NewComboBoxString = NewObject<UComboBoxString>(NewHorizontalBox);

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

		NewComboBoxString->SetSelectedOption(DataAssetSpacecrafts[Index]->InitialMaterial->GetName());

		//for (const TPair<UStaticMesh*, bool>& BongoPair : PlayerDataAssetSpacecrafts->SpacecraftMeshes)
		FString TargetStaticMesh = SauvegardePersonnalisation->LoadPlayerMeshFromFile(StaticMesh->GetName());
		FButtonStyle ButtonStyle = NewButton->GetStyle();
					
		if (StaticMesh->GetName() == TargetStaticMesh)
		{
			SetButtonGreen(ButtonStyle);
			EquipedMesh.Add(StaticMesh);
		}
		NewButton->SetStyle(ButtonStyle);
		ButtonsMeshes.Add(NewButton, StaticMesh);
	}
	SauvegardePersonnalisation->SavePlayerMeshToFile(EquipedMesh);
	AttachClickedEvent();
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
	
	if (!PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh))
	{
		PlayerDataAssetSpacecrafts->SpacecraftMeshes.Add(TargetMesh);
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