// Fill out your copyright notice in the Description page of Project Settings.


#include "TDBuildingsManager.h"

ATDBuildingsManager::ATDBuildingsManager(){
	PrimaryActorTick.bCanEverTick = true;

	Time = 5.0f;
}

// Called when the game starts or when spawned
void ATDBuildingsManager::BeginPlay(){
	Super::BeginPlay();
	GameMode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ATDBuildingsManager::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

bool ATDBuildingsManager::CheckConstruct(TurretsTypes Type){
	if (!GameMode) {
		GameMode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
	}
	
	if (GameMode) {	
		switch (Type) {
			case TurretsTypes::FlamethrowerTurret: {
				if (GameMode->ChangeGold(TurretsCost::FlamethrowerTurretCost)) {
					return true;
				}
			}
			case	 TurretsTypes::CannonTurret: {
				if (GameMode->ChangeGold(TurretsCost::CannonTurretCost)) {
					return true;
				}
			}
			case TurretsTypes::CrossbowTurret: {
				if (GameMode->ChangeGold(TurretsCost::CrossbowTurretCost)) {
					return true;
				}
			}
		}		
	}
	return false;
}

void ATDBuildingsManager::InitConstruction(TurretsTypes Type, FTransform Location){
	FActorSpawnParameters SpawnParams;
	switch (Type) {
		case TurretsTypes::FlamethrowerTurret: {
			ATDFlamethrowerTurret* Turret = GetWorld()->SpawnActor<ATDFlamethrowerTurret>(ATDFlamethrowerTurret::StaticClass(), Location, SpawnParams);
			if (Turret) {
				Turret->Initialise(Time);
			}
			return;
		}
		case TurretsTypes::CannonTurret: {
			ATDCannonTurret* Turret = GetWorld()->SpawnActor<ATDCannonTurret>(ATDCannonTurret::StaticClass(), Location, SpawnParams);
			if (Turret) {
				Turret->Initiliaze(Time);
			}
			return;
		}
		case TurretsTypes::CrossbowTurret: {
			ATDCrossbowTurret* Turret = GetWorld()->SpawnActor<ATDCrossbowTurret>(ATDCrossbowTurret::StaticClass(), Location, SpawnParams);
			if (Turret) {
				Turret->Initialize(Time);
			}
			return;
		}
	}
}


