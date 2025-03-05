#include "Personnalisation/Personnalisation.h"

#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "Personnalisation/DataAsset/PlayerSpacecraft.h"

APersonnalisation::APersonnalisation(): MaxIndex(0), ActualMaterial(nullptr), LockSpacecraft(nullptr)
{
}

void APersonnalisation::BeginPlay()
{
	Super::BeginPlay();
	GetValidDataAssetSpacecraft(0);
	MaxIndex = DataAssetSpacecrafts.Num() - 1;
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
			ActualMaterial = PlayerDataAssetSpacecrafts->Material;
		}
		else
		{
			LockSpacecraft->SetVisibility(ESlateVisibility::Hidden);
			ActualMaterial = DataAssetSpacecrafts[_Index]->Material;
		}
	}
}

void APersonnalisation::CreateChildrenForDetailCustom(UVerticalBox* ListObject)
{
	if (!ListObject) return;
	
	ListObject->ClearChildren();
	
	if (DataAssetSpacecrafts[Index]->IsChoose)
	{
		for (const TPair<UStaticMesh*, bool>& Pair : DataAssetSpacecrafts[Index]->SpacecraftMeshes)
		{
			const UStaticMesh* StaticMesh = Pair.Key;

			if (StaticMesh)
			{
				FString MeshName = StaticMesh->GetName();

				UHorizontalBox* NewHorizontalBox = NewObject<UHorizontalBox>(ListObject);
				UButton* NewButton = NewObject<UButton>(NewHorizontalBox);
				UTextBlock* NewTextBlock = NewObject<UTextBlock>(NewButton);
				UComboBoxString* NewComboBoxString = NewObject<UComboBoxString>(NewHorizontalBox);

				NewTextBlock->SetText(FText::FromString(MeshName));

				NewButton->AddChild(NewTextBlock);
				NewHorizontalBox->AddChild(NewButton);
				NewHorizontalBox->AddChild(NewComboBoxString);
				ListObject->AddChild(NewHorizontalBox);

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
			}
		}
	}
}

void APersonnalisation::SwitchMaterialPlayer()
{
	
}

