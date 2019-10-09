// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDSpectatorPawn.h"
#include "TDPlayerController.h"
#include "UI/TDHUD.h"
#include "Containers/Array.h"
#include "TDDwarf.h"
#include "TDWayPoint.h"
#include "TowerDefenceGameModeBase.generated.h"

UCLASS()
class TOWERDEFENCE_API ATowerDefenceGameModeBase : public AGameModeBase{
	GENERATED_BODY()

public:
	ATowerDefenceGameModeBase();

	virtual void BeginPlay() override;

	void SetGamePaused();

	bool ChangeGold(const unsigned& Price);

	void Restart();

	void CloseGame();

	virtual void Tick(float DeltaTime) override;

	void SetGameEnded(const float& BreweryHealth);

private:
	UFUNCTION()
		void OnDwarfDestroyed(AActor* Actor);

	int32 MaxNum();

	TArray<TArray<int32> > SpawnArray;

	TArray<ATDWayPoint*> WayPoints;

	UPROPERTY(EditAnywhere)
		FVector SpawnLocation;

	UPROPERTY(EditAnywhere)
		FRotator SpawnRotation;

	ATDHUD* HUD;

	ATDPlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
		unsigned CurrentGold;

	UPROPERTY(EditAnywhere)
		unsigned MaxWave;

	UPROPERTY(EditAnywhere)
		unsigned CurrentWave;


	UPROPERTY(EditAnywhere)
		float WaveMaxTimer;

	UPROPERTY(EditAnywhere)
		float WaveCurrentTimer;

	UPROPERTY(EditAnywhere)
		float SpawnMaxTimer;

	UPROPERTY(EditAnywhere)
		float SpawnCurrentTimer;

	bool bWaveUpdated;

	bool bCanSpawn;

};
