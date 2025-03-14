#include "Player/HoverController.h"

#include "Personnalisation/PossibilityDataCombinaison.h"
#include "Personnalisation/DataAsset/DataAssetSpacecraft.h"
#include "NiagaraComponent.h"

AHoverController::AHoverController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), PlayerSpacecraft(nullptr), LengthSpacecraftMesh(0), AngularRotSpeed(0),
	  ThrustSpeed(0), SpinImpulseTopForce(0), SpinReverseForce(0), LateralForceReduction(0),
	  SpeedToForceFactor(0), AngularSpeedToForceFactor(0), Damping(0), Stifness(0)
{    
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Movable);

	ActualEngineNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	ActualEngineNiagara->SetMobility(EComponentMobility::Movable);
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

	ActualEngineNiagara->AttachToComponent(MeshesComponents[0], FAttachmentTransformRules::KeepRelativeTransform);
	SetupAttachmentMeshToHover();
}

void AHoverController::SetupAttachmentMeshToHover()
{	
	int Index = 0;
	
	for (const TPair<UStaticMesh*, FVector>& Pair : PlayerSpacecraft->SpacecraftMeshes)
	{
		UStaticMesh* StaticMesh = Pair.Key;
		FVector SpawnPos = Pair.Value;
		
		if (!MeshesComponents.IsValidIndex(Index)) return;
		
		UStaticMeshComponent* TargetMeshComponent = MeshesComponents[Index];
		TargetMeshComponent->SetStaticMesh(StaticMesh);
		
		if (Index == 0)
		{
			TargetMeshComponent->SetSimulatePhysics(true);
			TargetMeshComponent->SetMassOverrideInKg(NAME_None, PlayerSpacecraft->Mass, true);
		}
		
		TargetMeshComponent->SetRelativeLocation(SpawnPos);

		if (StaticMesh->GetName() == "SM_Vortex_Spoiler2") TargetMeshComponent->SetRelativeRotation(FRotator(0, 180.0, 0));
		else if (StaticMesh->GetName() == "SM_Vortex_Engine4") TargetMeshComponent->SetRelativeRotation(FRotator(-90.0, 0, 0));
		else TargetMeshComponent->SetRelativeRotation(FRotator(0, 0, 0));

		SetupNiagaraEngine(StaticMesh->GetName());
		
		Index++;
	}

	SetupInput();
	SetupVariable();
}

void AHoverController::SetupVariable()
{
	for (int i = 0; i < PossibilityDataCombinaison.Num(); i++)
	{
		if (PossibilityDataCombinaison[i]->NumbersOfMesh == PlayerSpacecraft->SpacecraftMeshes.Num())
		{
			AngularRotSpeed = PossibilityDataCombinaison[i]->AngularRotSpeed;
			ThrustSpeed = PossibilityDataCombinaison[i]->ThrustSpeed;
			SpinImpulseTopForce = PossibilityDataCombinaison[i]->SpinImpulseTopForce;
			SpinReverseForce = PossibilityDataCombinaison[i]->SpinReverseForce;
			LateralForceReduction = PossibilityDataCombinaison[i]->LateralForceReduction;
			SpeedToForceFactor = PossibilityDataCombinaison[i]->SpeedToForceFactor;
			AngularSpeedToForceFactor = PossibilityDataCombinaison[i]->AngularSpeedToForceFactor;
			Damping = PossibilityDataCombinaison[i]->Damping;
			Stifness = PossibilityDataCombinaison[i]->Stifness;

			break;
		}
	}
}

void AHoverController::SetupNiagaraEngine(const FString& StaticMeshName)
{
	if (!ActualEngineNiagara) return;

	TArray<UNiagaraSystem*> Lists;
	TArray<FTransform> ListTransforms;

	UNiagaraSystem* SelectedSystem = nullptr;

	for (const auto& Elem : EnginesNiagara)
	{
		SelectedSystem = Elem.Key;
		FTransform SelectedLocation = Elem.Value;

		Lists.Add(SelectedSystem);
		ListTransforms.Add(SelectedLocation);
	}

	if (StaticMeshName == "SM_Vortex_Engine2") ActualEngineNiagara->SetAsset(Lists[0]);
	if (StaticMeshName == "SM_Vortex_Engine1") ActualEngineNiagara->SetAsset(Lists[1]);
	if (StaticMeshName == "SM_Vortex_Engine4") ActualEngineNiagara->SetAsset(Lists[2]);
    
	if (SelectedSystem)
	{
		if (StaticMeshName == "SM_Vortex_Engine2") ActualEngineNiagara->SetRelativeTransform(ListTransforms[0]);
		if (StaticMeshName == "SM_Vortex_Engine1") ActualEngineNiagara->SetRelativeTransform(ListTransforms[1]);
		if (StaticMeshName == "SM_Vortex_Engine4") ActualEngineNiagara->SetRelativeTransform(ListTransforms[2]);
	}

	ActualEngineNiagara->Activate();
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

