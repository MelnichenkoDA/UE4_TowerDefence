// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Containers/Map.h"
#include "TDSpectatorPawn.generated.h"

UCLASS()
class TOWERDEFENCE_API ATDSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:

	ATDSpectatorPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);	

	void OnClickEscape();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponentCollision;

	FVector MovementInput;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	TMap<FString, bool*> BlockedDirections;

	bool bCanMoveRight;
	bool bCanMoveLeft;

	bool bCanMoveForward;
	bool bCanMoveBackward;
};
