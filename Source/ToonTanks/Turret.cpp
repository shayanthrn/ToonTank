// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Tank){
		if(IsInFireRange()){
			TurretAim(Tank->GetActorLocation());
		}
	}
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition(){
	if(Tank){
		if(IsInFireRange()){
			Fire();
		}
	}
}

bool ATurret::IsInFireRange(){
	float distance = FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
	if(distance<range){
		return true;
	}
	return false;
}

void ATurret::Destruction(){
	Super::Destruction();
	Destroy();
}