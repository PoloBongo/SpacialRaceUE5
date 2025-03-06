#include "Player/HoverController.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

AHoverController::AHoverController(): PlayerSpacecraft(nullptr), AngularRotSpeed(0), ThrustSpeed(0),
                                      SpinImpulseTopForce(0),
                                      SpinReverseForce(0),
                                      LateralForceReduction(0),
                                      SpeedToForceFactor(0),
                                      AngularSpeedToForceFactor(0),
                                      Damping(0), Stifness(0)
{
	//Initialize();
}

void AHoverController::Initialize(int _Length)
{
	LengthSpacecraftMesh = _Length;
	UE_LOG(LogTemp, Warning, TEXT("1 : %d"), LengthSpacecraftMesh);
	if (LengthSpacecraftMesh < MeshesComponents.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("2"));
		for (int i = MeshesComponents.Num() - 1; i >= LengthSpacecraftMesh; --i)
		{
			UE_LOG(LogTemp, Warning, TEXT("3"));
			UStaticMeshComponent* MeshComponent = MeshesComponents[i];
            
			if (MeshComponent != nullptr && MeshComponent->GetStaticMesh() == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("4"));
				MeshComponent->DestroyComponent();
				MeshesComponents.RemoveAt(i);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("5"));
		for (int i = 0; i < LengthSpacecraftMesh; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("6"));
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

	SetupInput();
	SetupVariable();
}

void AHoverController::SetupVariable()
{
	AngularRotSpeed = PlayerSpacecraft->AngularRotSpeed;
	ThrustSpeed = PlayerSpacecraft->ThrustSpeed;
	SpinImpulseTopForce = PlayerSpacecraft->SpinImpulseTopForce;
	SpinReverseForce = PlayerSpacecraft->SpinReverseForce;
	LateralForceReduction = PlayerSpacecraft->LateralForceReduction;
	SpeedToForceFactor = PlayerSpacecraft->SpeedToForceFactor;
	AngularSpeedToForceFactor = PlayerSpacecraft->AngularSpeedToForceFactor;
	Damping = PlayerSpacecraft->Damping;
	Stifness = PlayerSpacecraft->Stifness;
}

void AHoverController::SetupInput_Implementation()
{
	// nada, l'event est géré en blueprint
}


void AHoverController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHoverController::SetLengthSpacecraftMesh(int _Length)
{
	LengthSpacecraftMesh = _Length;
}

