// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	SmokingTrailComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile trail"));
	RootComponent = MeshComp;
	SmokingTrailComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),LaunchSound,GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* HitedActor,UPrimitiveComponent* HitedComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	auto owner = GetOwner();
	if(owner == nullptr) return;
	auto controller = owner->GetInstigatorController();
	auto damageType = UDamageType::StaticClass();
	if(HitedActor && HitedActor!=this && HitedActor != owner){
		UGameplayStatics::ApplyDamage(HitedActor, damage, controller, this, damageType);
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCS);
		Destroy();
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle,HitResult.ImpactPoint);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),HitSound,GetActorLocation());

}

