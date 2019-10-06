// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDSpectatorPawn.h"
#include "TDPlayerController.h"
#include "UI/TDHUD.h"
#include "TowerDefenceGameModeBase.generated.h"

UCLASS()
class TOWERDEFENCE_API ATowerDefenceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATowerDefenceGameModeBase();

	virtual void BeginPlay() override;

	void SetGamePaused();

	bool ChangeGold(const unsigned& Price);

	void CloseGame();

private:
	ATDHUD* HUD;

	ATDPlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
		unsigned CurrentGold;

	UPROPERTY(EditAnywhere)
		unsigned CurrentWave;

	UPROPERTY(EditAnywhere)
		float Timer;

	unsigned CurrentEnemies;


};
