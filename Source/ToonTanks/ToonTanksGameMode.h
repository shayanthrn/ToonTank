// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_EndGame(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* PlayerController;
	float StartDelay=3.f;
	void GameStart();
	int32 NumberOfturrets = 0;
	int32 CountTurrets();
};
