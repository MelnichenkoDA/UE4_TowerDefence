// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TDWayPoint.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDWayPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNextPoint(ATDWayPoint* Point);

	ATDWayPoint* GetNextPoint();

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponentCollision;

	UPROPERTY(EditAnywhere)
		ATDWayPoint* NextPoint;
};
