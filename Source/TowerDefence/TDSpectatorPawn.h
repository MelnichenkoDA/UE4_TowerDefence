// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Camera/CameraComponent.h"
#include "TDSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ATDSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:

	ATDSpectatorPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);	

	void OnClickEscape();

protected:
	virtual void BeginPlay() override;

private:
	UCameraComponent* Camera;

	FVector MovementInput;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	UPROPERTY(EditAnywhere)
		float MinY;

	UPROPERTY(EditAnywhere)
		float MaxY;

	UPROPERTY(EditAnywhere)
		float MinX;

	UPROPERTY(EditAnywhere)
		float MaxX;

};
