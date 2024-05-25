// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	void Destruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class ATank* Tank;
	UPROPERTY(EditAnywhere)
	float range=300.f;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;
	void CheckFireCondition();
	bool IsInFireRange();
};
