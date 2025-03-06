#include "Player/HoverControllerShowRoom.h"

AHoverControllerShowRoom::AHoverControllerShowRoom(): MainComponent(nullptr)
{
}

void AHoverControllerShowRoom::BeginPlay()
{
	Super::BeginPlay();
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