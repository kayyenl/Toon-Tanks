// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

	private:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

		FVector MoveDirection;
		FQuat RotationDirection;

		UPROPERTY(EditAnywhere, Category = "MOVEMENT SPEEDS")
		float MoveSpeed = 100.f;
		UPROPERTY(EditAnywhere, Category = "MOVEMENT SPEEDS")
		float TurnSpeed = 100.f;

		bool bIsPlayerAlive = true;

		APlayerController* PlayerControllerRef;

		void CalculateMoveInput(float Value);
		void CalculateRotateInput(float Value);  //value is being created for access binding.

		void Move();
		void Rotate();


	public:

		APawnTank();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		virtual void HandleDestruction() override;

		bool GetIsPlayerAlive();
		
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	
};
