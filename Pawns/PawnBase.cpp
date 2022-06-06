// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actor/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values 
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Default Subobject: The function that will be creating and adding components inside our existing class.
	CapsuleCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("The Capsule Collider")); 
	//Since this is the first component, it will be defined as the root component.
	RootComponent = CapsuleCompo;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Base Mesh"));
	//We need to make sure that the basemesh is in the correct posn of the hierarchy, as the mesh needs to inherit movement and rotation of the capcomp.
	BaseMesh -> SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("The Projectile Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("The Health Bar"));
}

void APawnBase::RotateTurretFunction(FVector LookAtTarget) 
{
	//Update TurretMesh rotation to face towards the LookAtTarget passed in from Child Classes.
	//TurretMesh -> SetWorldRotation()...

	FVector LookAtTurretCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh -> GetComponentLocation().Z);     //this value will be passed into the setworldrotation function to make turretmesh face target.
	FVector StartingLocation = TurretMesh -> GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTurretCleaned -  StartingLocation).Rotation();
	TurretMesh -> SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() 
{
	//After getting ProjectileSpawnPoint Location & Rotation, -> Spawn Projectile class at Location firing towards Rotation.
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint -> GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint -> GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld() -> SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile -> SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	//Universal -> Death effects particle, sound and camera shake.
	
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(DeathShake);
}

// Called when the game starts or when spawned


