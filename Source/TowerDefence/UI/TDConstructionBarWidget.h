// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/ProgressBar.h"
#include "TDConstructionBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UTDConstructionBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTDConstructionBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	void SetPositionAndTime(const FVector& Position, const float& Time, bool * bConstructed);	

private:
	FVector TargetPosition;
	
	UPanelWidget* Panel;

	UPROPERTY(EditAnywhere)
		UProgressBar* ProgressBar;

	UCanvasPanelSlot* BarSlot;

	APlayerController const * PlayerController;

	float MaxTime;
	float CurrentTime;

	bool* bFinished;
};
