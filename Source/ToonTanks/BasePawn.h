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
	void Destruction();
	
protected:
	void TurretAim(FVector LookAtTarget);
	void Fire();


private:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* DestructionParticle;
	UPROPERTY(EditAnywhere)
	class USoundBase* DestructionSound;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DestructionCS;
};
