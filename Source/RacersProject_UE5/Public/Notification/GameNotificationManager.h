#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameNotificationManager.generated.h"

/* Structure du message de notification */
USTRUCT(BlueprintType)
struct FNotification
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Message; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color;

	FNotification() : Message(TEXT("Default Message")), Color(FLinearColor::White) {}
};

UCLASS()
class RACERSPROJECT_UE5_API AGameNotificationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameNotificationManager();

static AGameNotificationManager* GetInstance(UWorld* World);

	/* Permet de lancer une notification */
	void SetTextNotification(FString NewNotification, FColor Color);
	void ShowNotification(const FNotification& NewNotification);
	FString GetTextNotification();
protected:
	virtual void BeginPlay() override;
private:
	/* texte de la notification*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	FString TextNotification;
	
	FTimerHandle NotificationHandle;
	FTimerManager NotificationManager;

	/* user widget (ui) de la notification*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(AllowPrivateAccess="true"))
	UUserWidget* NotificationWidget;

	/* temps de la notification*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(AllowPrivateAccess="true"))
	float NotificationDuration;

	/* Système de queue pour les notif*/
	TQueue<FNotification> NotificationQueue;
	
	void HiddeNotification();
	void ProcessNextNotification();

	static AGameNotificationManager* Instance;
};
