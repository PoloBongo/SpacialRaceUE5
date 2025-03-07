#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartRace.generated.h"

class ASauvegardePersonnalisation;
class AHoverController;
/**
 * 
 */
UCLASS()
class RACERSPROJECT_UE5_API UStartRace : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable)
	void StartRace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AHoverController> HoverController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	FVector SpawnPos;

	/* Save Personnalisation Part */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Personnalisation Save", meta=(AllowPrivateAccess="true"))
	ASauvegardePersonnalisation* SauvegardePersonnalisation;
};
