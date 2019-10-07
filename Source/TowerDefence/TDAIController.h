// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "TDAIController.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDAIController : public AAIController
{
	GENERATED_BODY()

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	void MoveToTarget();

private:
	ATargetPoint* TargetPoint;
};
