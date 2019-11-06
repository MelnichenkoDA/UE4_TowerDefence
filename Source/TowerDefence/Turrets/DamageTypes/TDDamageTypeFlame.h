// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "TDDamageTypeFlame.generated.h"

UCLASS()
class TOWERDEFENCE_API UTDDamageTypeFlame : public UDamageType
{
	GENERATED_BODY()
	
public:
	UTDDamageTypeFlame();

	void InitDamage(float& Timer);

private:
	static float Timer;
};
