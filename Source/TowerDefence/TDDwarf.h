// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"
#include "TDAIController.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TDDamageTypeFlame.h"
#include "GameFramework/Character.h"
#include "TDDwarf.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDDwarf : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDDwarf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	const bool& IsAlive();

private:
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalComponent;

	UPROPERTY(EditAnywhere)
	UAnimSequence* AnimationDeath;

	UAnimSequence* AnimationMoveFrd;	

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleComponentBurn;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleComponentBlood;

	UPROPERTY(EditAnywhere)
		float HealthPoints;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	UPROPERTY(EditAnywhere)
		float Damage	;	

	float ContiniusDamageTimer;
	float ContiniusDamage;

	float DestroyingTimer;

	bool bIsUnderFlame;
	bool bIsAlive;


};
