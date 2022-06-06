// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretList; //doesnt need to be APawnTurret because we arent going to be referencing any APawnTurret specific properties from the array.
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretList);
    return TurretList.Num();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{   
    if (DeadActor == PlayerTank)
    {
        PlayerTank -> HandleDestruction();
        HandleGameOver(false);
        if (PlayerControllerRef)
        {
            PlayerControllerRef -> SetPlayerEnabledState(false);
        }
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret -> HandleDestruction();
        NumTurrets--;
        if (NumTurrets <= 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart() 
{
    //initialise the start countdown, turrets, and pawn check
    //calling bp gamwstart.
    NumTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();
    if (PlayerControllerRef)
        {
            PlayerControllerRef -> SetPlayerEnabledState(false);

            FTimerHandle PlayerEnableHandle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, 
            &APlayerControllerBase::SetPlayerEnabledState, true);  //class of function called, address of function, and the parameters passed into it.
            GetWorld() -> GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
        }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    //if all turrets have been destroyed, show win.
    //if player has died, show lost and call gameover(bool) from the bp.
    GameOver(PlayerWon);
}

