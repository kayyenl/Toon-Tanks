// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();	


    GetWorld() -> GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    //cast from APawn to APawnTank class.
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));    //finding the APawn class returned from the 0 index, store as APawnTank class.
    //this is a method var.
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurretFunction(PlayerPawn -> GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    // Check if the player is valid
    // Check if the player has entered the range of turret THEN FIRE 
    if (!PlayerPawn || !PlayerPawn -> GetIsPlayerAlive())
    {
        return;
    }
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if (!PlayerPawn)
    {
        return 0.f;
    }

    return FVector::Dist(PlayerPawn -> GetActorLocation(), GetActorLocation());
    
}
