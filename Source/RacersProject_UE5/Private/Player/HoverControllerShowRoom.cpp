#include "Player/HoverControllerShowRoom.h"

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
	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent != nullptr && MeshComponent->GetStaticMesh() == nullptr)
		{
			if (UStaticMesh* DefaultMesh = TargetMesh)
			{
				MeshComponent->SetStaticMesh(DefaultMesh);
				break;
			}
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