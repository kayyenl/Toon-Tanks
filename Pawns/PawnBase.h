// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;        //Collection of data which contails transform.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	//VARIABLES
	UPROPERTY(EditAnywhere, Category = "Projectile Type")
	TSubclassOf<AProjectileBase> ProjectileClass; //check again

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> DeathShake; 

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DeathSound;

public:
	// Sets default values for this pawn's properties
	APawnBase();
	
	virtual void HandleDestruction(); 

protected: 

	void RotateTurretFunction(FVector LookAtTarget);
	
	void Fire();



};
