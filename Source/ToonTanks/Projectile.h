// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere)
	float damage=35;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComp;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* SmokingTrailComp;
	UPROPERTY(EditAnywhere)
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* HitedActor,UPrimitiveComponent* HitedComp, FVector NormalImpulse, const FHitResult& HitResult);
};
