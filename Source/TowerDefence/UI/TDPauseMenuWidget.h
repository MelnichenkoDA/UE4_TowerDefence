// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "TDPauseMenuWidget.generated.h"

UCLASS()
class TOWERDEFENCE_API UTDPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTDPauseMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void OnContinueButtonClicked();

	UFUNCTION()
		void OnRestartButtonClicked();

	UFUNCTION()
		void OnExitButtonClicked();

	UPanelWidget* Panel;

	UTexture2D* TextureButton;

	UPROPERTY(EditAnywhere)
		UButton* ButtonContinue;

	UPROPERTY(EditAnywhere)
		UButton* ButtonRestart;

	UPROPERTY(EditAnywhere)
		UButton* ButtonExit;

	UPROPERTY(EditAnywhere)
		UCanvasPanel* HorizontalBoxContinue;
	
	UPROPERTY(EditAnywhere)
		UCanvasPanel* HorizontalBoxRestart;

	UPROPERTY(EditAnywhere)
		UCanvasPanel* HorizontalBoxExit;

	UPROPERTY(EditAnywhere)
		UImage* ImageButtonContinue;

	UPROPERTY(EditAnywhere)
		UImage* ImageButtonRestart;

	UPROPERTY(EditAnywhere)
		UImage* ImageButtonExit;	

	UPROPERTY(EditAnywhere)
		UTextBlock* TextBoxContinue;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextBoxRestart;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextBoxExit;
};
