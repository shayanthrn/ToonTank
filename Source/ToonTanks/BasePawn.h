// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
protected:
	void TurretAim(FVector LookAtTarget);


private:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;
};
