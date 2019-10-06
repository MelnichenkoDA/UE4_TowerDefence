// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDMainWidget.h"
#include "TDPauseMenuWidget.h"
#include "TDBuildingsMenuWidget.h"
#include "TDHUD.generated.h"


UCLASS()
class TOWERDEFENCE_API ATDHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATDHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void UpdateGold(const unsigned&);

	void UpdateWave(const unsigned&);

	void ShowPauseMenu();	

	void ClosePauseMenu();

	void ShowConstructionMenu(AActor * EmptyTurret);	

	void CloseCurrentMenu();	

	void CloseGame();

private:
	void CloseConstructionMenu();

	UPROPERTY(EditAnywhere)
		UTDMainWidget* MainWidget;

	UPROPERTY(EditAnywhere)
		UTDPauseMenuWidget* PauseWidget;

	UPROPERTY(EditAnywhere)
		UTDBuildingsMenuWidget* BuildingsWidget;

	AActor * SelectedActor;
};
