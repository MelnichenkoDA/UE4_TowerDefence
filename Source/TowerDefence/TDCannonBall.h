// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "TDDamageTypeCannon.h"
#include "Particles/ParticleSystemComponent.h"
#include "TDCannonBall.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDCannonBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDCannonBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(const FVector& TargetPosition, const float& Damage);
	
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshBall;	

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponentCollision;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleSystemTail;

	FVector TargetPosition;

	float Speed;

	float Damage;

	float LifeTime;

	bool bInitialized;

};
