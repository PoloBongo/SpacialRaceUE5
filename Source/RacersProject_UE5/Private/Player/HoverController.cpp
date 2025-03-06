#include "Player/HoverController.h"

#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"

AHoverController::AHoverController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), PlayerSpacecraft(nullptr), LengthSpacecraftMesh(0), AngularRotSpeed(0),
	  ThrustSpeed(0), SpinImpulseTopForce(0), SpinReverseForce(0), LateralForceReduction(0),
	  SpeedToForceFactor(0), AngularSpeedToForceFactor(0), Damping(0), Stifness(0)
{    
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AHoverController::Initialize(int _Length)
{
	LengthSpacecraftMesh = _Length;
	UE_LOG(LogTemp, Warning, TEXT("1 : %d"), LengthSpacecraftMesh);

	while (MeshesComponents.Num() > LengthSpacecraftMesh)
	{
		UStaticMeshComponent* MeshComponent = MeshesComponents.Pop();
		if (MeshComponent)
		{
			MeshComponent->DestroyComponent();
		}
	}

	for (int i = 0; i < LengthSpacecraftMesh; i++)
	{
		UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *FString::Printf(TEXT("Main %d"), i));
		MeshComponent->RegisterComponent();
		MeshesComponents.Add(MeshComponent);

		if (i == 0)
		{
			RootComponent = MeshComponent;
		}
		else
		{
			MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

