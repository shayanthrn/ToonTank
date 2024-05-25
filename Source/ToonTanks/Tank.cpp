// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank(){
        SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
        SpringArmComp-> SetupAttachment(RootComponent);
        CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
        CameraComp-> SetupAttachment(SpringArmComp);
        MoveSpeed = 100; //cm/s
        TurnRate = 30;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerController){
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,100.f,12,FColor::Black, false,-1.f);
        if(HitResult.GetActor()){
            TurretAim(HitResult.ImpactPoint);
        }
    }
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
}

void ATank::Move(float Value)
{
    
    if(Value != 0){
        FVector Deltavector = FVector::ZeroVector;
        Deltavector.X = Value*MoveSpeed*UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalOffset(Deltavector, true);
    }
    if(Value >= 0){
        reverseMove = false;
    }
    else{
        reverseMove = true;
    }
}

void ATank::Turn(float Value)
{
    
    if(Value != 0){
        if(reverseMove){
            Value *= -1;
        }
        FRotator Deltarotation = FRotator::ZeroRotator;
        Deltarotation.Yaw = Value*TurnRate*UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalRotation(Deltarotation, true);
    }
}