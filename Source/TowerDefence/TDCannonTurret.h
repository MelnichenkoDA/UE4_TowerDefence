// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "TDCannonBall.h"
#include "TDDwarf.h"
#include "UI/TDConstructionBarWidget.h"
#include "TDCannonTurret.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDCannonTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDCannonTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initiliaze(const float& Time);

private:
	UFUNCTION()
		void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshFoundation;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMeshCannon;

	UPROPERTY(EditAnywhere)
		UTDConstructionBarWidget* ConstructionBarWidget;

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionComponent;

	UParticleSystemComponent* ParticleComponentCreation;

	UAnimSequence* AnimationShooting;

	ATDDwarf* CurrentTarget;

	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		float ReloadMaxTime;

	UPROPERTY(EditAnywhere)
		float ReloadCurrentTime;

	float ConstructionTimer;

	TArray<AActor*> Targets;

	bool bConstructed;
};
