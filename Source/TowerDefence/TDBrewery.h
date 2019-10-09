// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TowerDefenceGameModeBase.h"
#include "TDBrewery.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDBrewery : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDBrewery();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:		
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UStaticMeshComponent* StaticMeshBrewery;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponentCollision;

	UPROPERTY(EditAnywhere)
		float HealthPoints;
};
