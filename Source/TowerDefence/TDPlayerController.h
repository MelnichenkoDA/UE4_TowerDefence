// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDSpectatorPawn.h"
#include "TDPlayerController.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATDPlayerController();

private:
	virtual void SetupInputComponent() override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void OnClickEscape();

	ATDSpectatorPawn* SpectatorPawn;
};
