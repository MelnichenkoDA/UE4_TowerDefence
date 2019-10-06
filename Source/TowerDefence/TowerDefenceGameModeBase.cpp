// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"

ATowerDefenceGameModeBase::ATowerDefenceGameModeBase() {
	PlayerControllerClass = ATDPlayerController::StaticClass();
	DefaultPawnClass = ATDSpectatorPawn::StaticClass();
	HUDClass = ATDHUD::StaticClass();

	CurrentGold = 50;
	CurrentWave = 1;
	Timer = 15.0f;
	CurrentEnemies = 25;
}

void ATowerDefenceGameModeBase::BeginPlay() {
	HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD) {
		HUD->UpdateGold(CurrentGold);
		HUD->UpdateWave(CurrentWave);
	}
	
	PlayerController = Cast<ATDPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
}

void ATowerDefenceGameModeBase::SetGamePaused() {
	if (PlayerController) {
		PlayerController->SetPause(!IsPaused());
	}
}

bool ATowerDefenceGameModeBase::ChangeGold(const unsigned& Price){
	if (CurrentGold >= Price) {	
		
		CurrentGold -= Price;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(Price));
		}
		HUD->UpdateGold(CurrentGold);
		return true;
	}
	return false;
}

void ATowerDefenceGameModeBase::CloseGame(){
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
