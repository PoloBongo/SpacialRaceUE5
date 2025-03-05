#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Personnalisation.generated.h"

class UBackgroundBlur;
class UDataAssetSpacecraft;

UCLASS()
class RACERSPROJECT_UE5_API APersonnalisation : public AActor
{
	GENERATED_BODY()
	
public:	
	APersonnalisation();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void ArrowLeft();

	UFUNCTION(BlueprintCallable)
	void ArrowRight();

	int Index = 0;
	int MaxIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	TArray<UDataAssetSpacecraft*> DataAssetSpacecrafts;

	void GetValidDataAssetSpacecraft(int _Index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UMaterial* ActualMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess="true"))
	UBackgroundBlur* LockSpacecraft;
};
