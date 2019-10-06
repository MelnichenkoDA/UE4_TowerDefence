// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "TDMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UTDMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTDMainWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

	void SetGold(const unsigned &);

	void SetWave(const unsigned &);


private:
	UFUNCTION()
		void OnMenuButtonClick();

	UPanelWidget* Panel;

	UTexture2D* TextureBorder;

	UTexture2D* TexturePauseButton;

	UPROPERTY(EditAnywhere)
		UImage* ImageGoldBorder;

	UPROPERTY(EditAnywhere)
		UImage* ImageWaveBorder;

	UPROPERTY(EditAnywhere)
		UImage* ImagePause;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextBoxGold;

	UPROPERTY(EditAnywhere)
		UTextBlock* TextBoxCurrentWave;
	
	UPROPERTY(EditAnywhere)
		UButton* ButtonMenu;

};
