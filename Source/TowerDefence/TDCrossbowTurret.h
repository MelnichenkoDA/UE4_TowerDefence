// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimSequence.h"
#include "TDCrossbowArrow.h"
#include "TDCrossbowTurret.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDCrossbowTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDCrossbowTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshFoundation;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMeshCrossbow;

	UPROPERTY(EditAnywhere)
		UAnimSequence* AnimationShooting;

	UPROPERTY(EditAnywhere)
		float ReloadMaxTime;

	UPROPERTY(EditAnywhere)
		float ReloadCurrentTime;

	UPROPERTY(EditAnywhere)
		float Damage;
};
