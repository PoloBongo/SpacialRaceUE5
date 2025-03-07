#include "Widget/StartRace.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "Player/HoverController.h"

void UStartRace::StartRace()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked with %d"), PlayerSpacecraft->SpacecraftMeshes.Num())

	AHoverController* SpawnHoverController = GetWorld()->SpawnActor<AHoverController>(HoverController, SpawnPos, FRotator::ZeroRotator);

	if (SpawnHoverController && PlayerSpacecraft)
	{
		SpawnHoverController->SetActorLocation(SpawnPos);
		SpawnHoverController->SetLengthSpacecraftMesh(PlayerSpacecraft->SpacecraftMeshes.Num());
		SpawnHoverController->Initialize(PlayerSpacecraft->SpacecraftMeshes.Num());
	}

	this->RemoveFromParent();
}
