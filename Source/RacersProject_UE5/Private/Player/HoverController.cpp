#include "Player/HoverController.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

AHoverController::AHoverController(): PlayerSpacecraft(nullptr)
{	
	for (int i = 0; i < Length; i++)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("Main %d"), i));
		MeshesComponents.Add(MeshComponent);

		if (i == 0)
		{
			RootComponent = MeshesComponents[0];
		}
		else
		{
			MeshesComponents[i]->SetupAttachment(RootComponent);
		}
	}
}

void AHoverController::BeginPlay()
{
	Super::BeginPlay();
	
	int Index = 0;
	for (const TPair<UStaticMesh*, bool>& Pair : PlayerSpacecraft->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		
		UStaticMeshComponent* TargetMeshComponent = MeshesComponents[Index];
		TargetMeshComponent->SetStaticMesh(StaticMesh);
		
		if (Index == 0)
		{
			TargetMeshComponent->SetSimulatePhysics(true);
			TargetMeshComponent->SetMassScale(NAME_None, PlayerSpacecraft->Mass);
		}
		
		Index++;
	}
}

void AHoverController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

