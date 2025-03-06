#include "Widget/StartRace.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "Player/HoverController.h"

void UStartRace::StartRace()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));

	AHoverController* SpawnHoverController = GetWorld()->SpawnActor<AHoverController>(HoverController, FVector(0, 0, 500), FRotator::ZeroRotator);

	if (SpawnHoverController && PlayerSpacecraft)
	{
		SpawnHoverController->SetActorLocation(FVector(0, 0, 500));
		SpawnHoverController->SetLengthSpacecraftMesh(PlayerSpacecraft->SpacecraftMeshes.Num());
	}

	this->RemoveFromParent();
}
