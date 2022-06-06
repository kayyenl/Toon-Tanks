// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("The Projectile Movement")); 
	//bcus dont belong in the scene hierarchy or inherit any transform, dont need to be a child component.
	ProjectileMoveComp -> InitialSpeed = MovementSpeed;
	ProjectileMoveComp -> MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("The Trail Particles"));
	ParticleTrail -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());

	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);   //Happens anytime a collision mesh on a class is registered.
	//OnComponentHit is When called.
	//AddDynamic adds a delegate, but still dk what is dynamic

}



void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	//UE_LOG(LogTemp, Warning, TEXT("Collided with %s"), *OtherActor -> GetName());
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)  //including this is to prevent nested components that overlap a collision w/ same class as projectile
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner -> GetInstigatorController(), this, DamageType);
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(HitShake);
		Destroy();
	}

}
