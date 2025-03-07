#include "Player/HoverController.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

AHoverController::AHoverController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), PlayerSpacecraft(nullptr), LengthSpacecraftMesh(0), AngularRotSpeed(0),
	  ThrustSpeed(0), SpinImpulseTopForce(0), SpinReverseForce(0), LateralForceReduction(0),
	  SpeedToForceFactor(0), AngularSpeedToForceFactor(0), Damping(0), Stifness(0)
{    
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Movable);
}

void AHoverController::Initialize(int _Length)
{
	LengthSpacecraftMesh = _Length;

	while (MeshesComponents.Num() > LengthSpacecraftMesh)
	{
		UStaticMeshComponent* MeshComponent = MeshesComponents.Pop();
		if (MeshComponent)
		{
			MeshComponent->DestroyComponent();
		}
	}
	
	for (int i = MeshesComponents.Num(); i <= LengthSpacecraftMesh; i++)
	{
		UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *FString::Printf(TEXT("Main %d"), i));

		if (!MeshComponent) return;

		MeshComponent->RegisterComponent();
		AddInstanceComponent(MeshComponent);

		if (i == 0 && MeshesComponents.Num() == 0)
		{
			MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			RootComponent = MeshComponent;
		}
		else
		{
			MeshComponent->AttachToComponent(MeshesComponents[0], FAttachmentTransformRules::KeepRelativeTransform);
		}

		MeshesComponents.Add(MeshComponent);
	}

	SetupAttachmentMeshToHover();
}

void AHoverController::SetupAttachmentMeshToHover()
{	
	int Index = 0;
	
	for (const TPair<UStaticMesh*, bool>& Pair : PlayerSpacecraft->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		
		if (!MeshesComponents.IsValidIndex(Index)) return;
		
		UE_LOG(LogTemp, Warning, TEXT("1 : %d\n2 : %s"), Index, *StaticMesh->GetName());
		
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

