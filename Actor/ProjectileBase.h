// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"


class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:


	UPROPERTY(EditAnywhere, Category = "PROJECTILE")
	UProjectileMovementComponent* ProjectileMoveComp;
	UPROPERTY(EditAnywhere, Category = "PROJECTILE")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystemComponent* ParticleTrail;


	UPROPERTY(EditAnywhere, Category = "PROJECTILE")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, Category = "BULLET")
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, Category = "BULLET")
	float Damage = 50;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> HitShake; 

	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
