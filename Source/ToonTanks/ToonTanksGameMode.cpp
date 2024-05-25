// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::BeginPlay(){
    Super::BeginPlay();
    GameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor){
    if(DeadActor == Tank){
        Tank->Destruction();
        if(PlayerController){
            PlayerController->SetEnableState(false);
        }
        BP_EndGame(false);
    }
    else if(ATurret* Deadturret = Cast<ATurret>(DeadActor)){
        Deadturret->Destruction();
        NumberOfturrets-=1;
        if(NumberOfturrets==0){
            BP_EndGame(true);
        }
    }
}

void AToonTanksGameMode::GameStart(){
    NumberOfturrets = CountTurrets();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    BP_StartGame();
    if(PlayerController){
        PlayerController->SetEnableState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(PlayerController,&AToonTanksPlayerController::SetEnableState,true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,InputDelegate,StartDelay,false);
    }
    
}

int32 AToonTanksGameMode::CountTurrets(){
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(this,ATurret::StaticClass(),actors);
    return actors.Num();
}