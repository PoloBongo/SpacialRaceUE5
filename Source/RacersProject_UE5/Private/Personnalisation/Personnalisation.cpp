#include "Personnalisation/Personnalisation.h"

#include "Components/BackgroundBlur.h"
#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

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
		}
		else
		{
			LockSpacecraft->SetVisibility(ESlateVisibility::Hidden);
		}
		ActualMaterial = DataAssetSpacecrafts[_Index]->Material;
	}
}

