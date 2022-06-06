// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("The Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("The Camera"));
    Camera -> SetupAttachment(SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();  //super call just does boom effect.
    // Include hiding logic later! 
    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive() 
{
    return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();

    if (PlayerControllerRef)
    {
        FHitResult CursorHit;
        PlayerControllerRef -> GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
        FVector CursorLocation = CursorHit.ImpactPoint;

        RotateTurretFunction(CursorLocation);
    }
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //parameter is a UInputComponent.
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent -> BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput); //will pass 1 or 0 float depending on the keys pressed.
    PlayerInputComponent -> BindAxis("Turn", this, &APawnTank::CalculateRotateInput);      //now fully bound to the movement input. he does the Calculate fns when the input is pressed.
    PlayerInputComponent -> BindAction("Fire", IE_Pressed, this, &APawnTank::Fire); //single press events, returning a state of either being pressed or released.
}


void APawnTank::CalculateMoveInput(float Value) 
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld() -> DeltaTimeSeconds, 0 , 0);
}

void APawnTank::CalculateRotateInput(float Value) 
{
    float RotateAmount = Value * TurnSpeed * GetWorld() -> DeltaTimeSeconds;
    FRotator Rotation = FRotator(0 , RotateAmount, 0 );   //Rotators are PYR oriented!
    RotationDirection = FQuat(Rotation);
}

void APawnTank::Move() //purpose is just for this function, addactorlocaloffset.
{
    AddActorLocalOffset(MoveDirection, true); //sweep is if collisions should be checked when actor/pawn is moving. false would allow wall phasing.
}

void APawnTank::Rotate() //purpose is just for this function, addactorlocaldirection.
{
    AddActorLocalRotation(RotationDirection, true);
}




