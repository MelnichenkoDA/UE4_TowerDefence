// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGameModeBase.h"
#include "UI/TDHUD.h"
#include "TDBuildingsTypes.hpp"
#include "TDEmptyTyrret.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDEmptyTyrret : public AActor
{
	GENERATED_BODY()
	
public:
	ATDEmptyTyrret();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;	

	bool StartConstruction(TurretsTypes Type);

private:
	UFUNCTION()
	void OnMouseClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);
	
private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StoneMeshComponent;	

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* TurretMeshComponent;

	static AActor* Manager;

	float Timer;	

	bool bUnderConstruction;
};
