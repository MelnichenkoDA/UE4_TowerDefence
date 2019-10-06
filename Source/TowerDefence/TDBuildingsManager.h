// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDBuildingsTypes.hpp"
#include "TowerDefenceGameModeBase.h"
#include "TDEmptyTyrret.h"
#include "TDFlamethrowerTurret.h"
#include "TDCannonTurret.h"
#include "TDBuildingsManager.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDBuildingsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDBuildingsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckConstruct(TurretsTypes Type);

	void InitConstruction(TurretsTypes Type, FTransform Location);

private:
	ATowerDefenceGameModeBase* GameMode;

	float Time;

};
