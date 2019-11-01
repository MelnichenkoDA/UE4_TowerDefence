// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "../TDBuildingsTypes.hpp"
#include "TDBuildingsMenuWidget.generated.h"

UCLASS()
class TOWERDEFENCE_API UTDBuildingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTDBuildingsMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void SetCurrentTurret( AActor *  Turret);

private:
	UFUNCTION()
		void OnFlameButtonCLicked();

	UFUNCTION()
		void OnCannonButtonClicked();

	UFUNCTION()
		void OnCrossbowButtonClicked();
	  
	void InitButtonFlame();
	void InitButtonCannon();
	void InitButtonCrossbow();

	void ButtonClicked(TurretsTypes Type);

	AActor * CurrentTurret;

	UPanelWidget* Panel;

	UTexture2D* TextureBorder;

	UTexture2D* TextureFlame;

	UTexture2D* TextureCannon;

	UTexture2D* TextureCrossbow;

	UPROPERTY(EditAnywhere)
		UButton* ButtonFlameTurret;

	UPROPERTY(EditAnywhere)
		UButton* ButtonCannonTurret;

	UPROPERTY(EditAnywhere)
		UButton* ButtonCrossbowTurret;

	UPROPERTY(EditAnywhere)
		UCanvasPanel* CanvasPanelFlame;

	UPROPERTY(EditAnywhere)
		UCanvasPanel* CanvasPanelCannon;

	UPROPERTY(EditAnywhere)
		UCanvasPanel* CanvasPanelCrossbow;

	UPROPERTY(EditAnywhere)
		UImage* ImageBorder;

	UPROPERTY(EditAnywhere)
		UImage* ImageFlameTurret;

	UPROPERTY(EditAnywhere)
		UImage* ImageCanonTurret;

	UPROPERTY(EditAnywhere)
		UImage* ImageCrossbowTurret;		

	UPROPERTY(EditAnywhere)
		UTextBlock* TextFlameCost;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextCannonCost;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextCrossbowCost;
};
