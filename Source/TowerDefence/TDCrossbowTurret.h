// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimSequence.h"
#include "TDCrossbowArrow.h"
#include "Particles/ParticleSystemComponent.h"
#include "UI/TDConstructionBarWidget.h"
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

	void Initialize(const float& Time);

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshFoundation;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMeshCrossbow;

	UPROPERTY(EditAnywhere)
		UAnimSequence* AnimationShooting;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleComponentCreation;

	UPROPERTY(EditAnywhere)
		UTDConstructionBarWidget* ConstructionBarWidget;

	UPROPERTY(EditAnywhere)
		float ReloadMaxTime;

	UPROPERTY(EditAnywhere)
		float ReloadCurrentTime;

	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		float ArrowMovementSpeed;

	UPROPERTY(EditAnywhere)
		float ArrowLifeTime;

	bool bConstructed;
};
