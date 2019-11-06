// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "DamageTypes/TDDamageTypeArrow.h"
#include "TDCrossbowArrow.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDCrossbowArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDCrossbowArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(const float& Damage, const float& Speed, const float& LifeTime);

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshMidArrow;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshLeftArrow;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshRightArrow;	

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionCompoment;

	float LifeTime;

	float MovementSpeed;

	float Damage;
};
