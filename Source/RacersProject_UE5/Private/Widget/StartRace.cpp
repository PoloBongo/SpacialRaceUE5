#include "Widget/StartRace.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "Player/HoverController.h"

void UStartRace::StartRace()
{	
	AHoverController* SpawnHoverController = GetWorld()->SpawnActor<AHoverController>(HoverController, 	FVector(0.0, 0.0, 0.0), FRotator::ZeroRotator);

	if (SpawnHoverController && PlayerSpacecraft)
	{
		SpawnHoverController->SetLengthSpacecraftMesh(PlayerSpacecraft->SpacecraftMeshes.Num());
		SpawnHoverController->Initialize(PlayerSpacecraft->SpacecraftMeshes.Num());
	}

	this->RemoveFromParent();
}
