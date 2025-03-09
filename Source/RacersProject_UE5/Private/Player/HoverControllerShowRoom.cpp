#include "Player/HoverControllerShowRoom.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

AHoverControllerShowRoom::AHoverControllerShowRoom(): MainComponent(nullptr)
{
}

void AHoverControllerShowRoom::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MeshComponents.Num(); i++)
	{
		if (MeshComponents[i] != nullptr)
		{
			MeshComponents[i]->SetStaticMesh(nullptr);
		}
	}
}

void AHoverControllerShowRoom::SetupMeshComponents(UStaticMesh* TargetMesh)
{
	if (!PlayerDataAssetSpacecrafts || !TargetMesh) return;

	if (!PlayerDataAssetSpacecrafts->SpacecraftMeshes.Contains(TargetMesh)) return;

	FVector SpawnPos = PlayerDataAssetSpacecrafts->OriginalSpacecraft->SpacecraftMeshes[TargetMesh];

	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent != nullptr && MeshComponent->GetStaticMesh() == nullptr)
		{
			MeshComponent->SetStaticMesh(TargetMesh);
			MeshComponent->SetRelativeLocation(SpawnPos);
			if (TargetMesh->GetName() == "SM_Vortex_Spoiler2") MeshComponent->SetRelativeRotation(FRotator(0, 180.0, 0));
			else if (TargetMesh->GetName() == "SM_Vortex_Engine4") MeshComponent->SetRelativeRotation(FRotator(-90.0, 0, 0));
			else MeshComponent->SetRelativeRotation(FRotator(0, 0, 0));
			break;
		}
	}
}

void AHoverControllerShowRoom::DetachMeshComponents(UStaticMesh* TargetMesh)
{
	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent != nullptr && MeshComponent->GetStaticMesh() == TargetMesh)
		{
			MeshComponent->SetStaticMesh(nullptr);
			break;
		}
	}
}