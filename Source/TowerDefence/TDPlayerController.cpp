// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "TowerDefenceGameModeBase.h"

ATDPlayerController::ATDPlayerController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATDPlayerController::SetupInputComponent(){
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATDPlayerController::MoveRight);

	InputComponent->BindAction("Escape", IE_Pressed, this, &ATDPlayerController::OnClickEscape);
}

void ATDPlayerController::MoveForward(float AxisValue){
	ATDSpectatorPawn* Pawn = Cast<ATDSpectatorPawn>(GetPawn());
	if (Pawn) {
		Pawn->MoveForward(AxisValue);
	}	
}

void ATDPlayerController::MoveRight(float AxisValue){
	ATDSpectatorPawn* Pawn = Cast<ATDSpectatorPawn>(GetPawn());
	if (Pawn) {
		Pawn->MoveRight(AxisValue);
	}
}

void ATDPlayerController::OnClickEscape(){
	ATowerDefenceGameModeBase* Mode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->SetGamePaused();
	}
}


