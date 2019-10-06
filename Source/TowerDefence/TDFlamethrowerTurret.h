// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimSequence.h"
#include "UI/TDConstructionBarWidget.h"
#include "TDDamageTypeFlame.h"
#include "Components/BoxComponent.h"
#include "TDFlamethrowerTurret.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDFlamethrowerTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDFlamethrowerTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialise(const float & Timer);

private:
	UFUNCTION()
		void OnFlameBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 	int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnFlameEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* TurretMeshComponent;

	UPROPERTY(EditAnywhere)
		UTDConstructionBarWidget* ConstructionBarWidget;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FlameMeshComponent;	

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
		float Damage;

	bool bConstructed;

	


};
