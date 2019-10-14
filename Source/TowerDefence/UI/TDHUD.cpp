// Fill out your copyright notice in the Description page of Project Settings.


#include "TDHUD.h"
#include "TowerDefenceGameModeBase.h"

ATDHUD::ATDHUD() {
	MainWidget = CreateWidget<UTDMainWidget>(GetWorld(), UTDMainWidget::StaticClass());

	PauseWidget = CreateWidget<UTDPauseMenuWidget>(GetWorld(), UTDPauseMenuWidget::StaticClass());

	BuildingsWidget = CreateWidget<UTDBuildingsMenuWidget>(GetWorld(), UTDBuildingsMenuWidget::StaticClass());

	SelectedActor = nullptr;
}

void ATDHUD::DrawHUD(){
	Super::DrawHUD();		
}

void ATDHUD::BeginPlay(){
	Super::BeginPlay();
	
	MainWidget->AddToViewport();
}

void ATDHUD::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ATDHUD::UpdateGold(const unsigned& Gold){
	MainWidget->SetGold(Gold);
}

void ATDHUD::UpdateWave(const unsigned& Wave) {
	MainWidget->SetWave(Wave);
}

void ATDHUD::ShowPauseMenu() {
	ATowerDefenceGameModeBase* GameMode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->SetGamePaused();
		PauseWidget->AddToViewport();
	}
}

void ATDHUD::ClosePauseMenu(const unsigned int& Code) {
	ATowerDefenceGameModeBase* GameMode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		switch (Code) {
		case 0:
			if (!GameMode->GetGameFinished()) {
				GameMode->SetGamePaused();
				PauseWidget->RemoveFromViewport();
			}
			break;
		case 1:
			GameMode->Restart();
			break;
		case 2:
			GameMode->CloseGame();
			break;
		}
	}
}

void ATDHUD::ShowConstructionMenu(AActor * EmptyTurret) {
	if (!SelectedActor) {
		SelectedActor = EmptyTurret;
		BuildingsWidget->AddToViewport();
		BuildingsWidget->SetCurrentTurret(SelectedActor);
	} else {
		CloseCurrentMenu();
		SelectedActor = EmptyTurret;
		BuildingsWidget->AddToViewport();
		BuildingsWidget->SetCurrentTurret(SelectedActor);
	}
}

void ATDHUD::CloseCurrentMenu() {
	if (SelectedActor->GetClass()->GetName() == "TDEmptyTyrret") {		
		CloseConstructionMenu();
		return;
	}	
}

void ATDHUD::CloseConstructionMenu() {
	SelectedActor = nullptr;
	BuildingsWidget->RemoveFromViewport();
}
