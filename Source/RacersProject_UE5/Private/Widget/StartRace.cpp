#include "Widget/StartRace.h"

#include "Personnalisation/SauvegardePersonnalisation.h"
#include "Player/HoverController.h"

void UStartRace::StartRace()
{	
	AHoverController* SpawnHoverController = GetWorld()->SpawnActor<AHoverController>(HoverController, 	FVector(0.0, 0.0, 0.0), FRotator::ZeroRotator);

	if (SpawnHoverController && SauvegardePersonnalisation)
	{
		SpawnHoverController->SetLengthSpacecraftMesh(SauvegardePersonnalisation->GetArrayOfSave());
		SpawnHoverController->Initialize(SauvegardePersonnalisation->GetArrayOfSave());
	}

	this->RemoveFromParent();
}
