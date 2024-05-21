// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Colider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh-> SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh-> SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint-> SetupAttachment(TurretMesh);
}


void ABasePawn::TurretAim(FVector LookAtTarget){
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;
	TurretMesh->SetWorldRotation(FMath::RInterpConstantTo(TurretMesh->GetComponentRotation(),
								LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),200.f));
}
