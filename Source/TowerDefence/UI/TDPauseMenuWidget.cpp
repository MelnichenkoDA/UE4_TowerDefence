// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPauseMenuWidget.h"
#include "TDHUD.h"

UTDPauseMenuWidget::UTDPauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> BorderImage(TEXT("/Game/UI/MainMenu/BorderImage"));

	TextureButton = BorderImage.Object;
}

void UTDPauseMenuWidget::NativeConstruct(){
	Super::NativeConstruct();
}

bool UTDPauseMenuWidget::Initialize(){
	Super::Initialize();

	if (WidgetTree) {
		Panel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Panel"));

		if (Panel) {
			WidgetTree->RootWidget = Panel;
			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Panel->Slot);
			if (PanelSlot) {
				PanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				PanelSlot->SetOffsets(FMargin(0.0f, 0.0f));
			}		

			ButtonContinue = WidgetTree->ConstructWidget<UButton>();
			if (ButtonContinue) {
				InitButtonContinue();
			} 					

			ButtonRestart = WidgetTree->ConstructWidget<UButton>();
			if (ButtonRestart) {
				InitButtonRestart();
			}

			ButtonExit = WidgetTree->ConstructWidget<UButton>();
			if (ButtonExit) {
				InitButtonExit();
			}
		}
	}

	return true;
}

void UTDPauseMenuWidget::InitButtonContinue() {
	Panel->AddChild(ButtonContinue);
	ButtonContinue->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);

	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonContinue->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetAnchors(FAnchors(0.45f, 0.4f));
	}

	HorizontalBoxContinue = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (HorizontalBoxContinue) {
		ButtonContinue->AddChild(HorizontalBoxContinue);

		ImageButtonContinue = WidgetTree->ConstructWidget<UImage>();
		if (ImageButtonContinue) {
			HorizontalBoxContinue->AddChild(ImageButtonContinue);

			ImageButtonContinue->SetBrushFromTexture(TextureButton);
			ImageButtonContinue->SetRenderScale(FVector2D(1.5, 3));
			ImageButtonContinue->SetRenderTranslation(FVector2D(24, 25));
		}

		TextBoxContinue = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextBoxContinue) {
			HorizontalBoxContinue->AddChild(TextBoxContinue);

			TextBoxContinue->SetVisibility(ESlateVisibility::Visible);
			TextBoxContinue->SetRenderTranslation(FVector2D(30.0f, 25.0f));
			TextBoxContinue->SetText(FText::FromString("Continue"));

			TextBoxContinue->Font.Size = 16;
			TextBoxContinue->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonContinue->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnContinueButtonClicked);
}

void UTDPauseMenuWidget::InitButtonRestart() {
	Panel->AddChild(ButtonRestart);
	ButtonRestart->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);

	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonRestart->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetAnchors(FAnchors(0.45f, 0.48f));
	}

	HorizontalBoxRestart = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (HorizontalBoxRestart) {
		ButtonRestart->AddChild(HorizontalBoxRestart);

		ImageButtonRestart = WidgetTree->ConstructWidget<UImage>();
		if (ImageButtonRestart) {
			HorizontalBoxRestart->AddChild(ImageButtonRestart);

			ImageButtonRestart->SetBrushFromTexture(TextureButton);
			ImageButtonRestart->SetRenderScale(FVector2D(1.5, 3));
			ImageButtonRestart->SetRenderTranslation(FVector2D(24, 25));
		}

		TextBoxRestart = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextBoxRestart) {
			HorizontalBoxRestart->AddChild(TextBoxRestart);

			TextBoxRestart->SetVisibility(ESlateVisibility::Visible);
			TextBoxRestart->SetRenderTranslation(FVector2D(40, 25));
			TextBoxRestart->SetText(FText::FromString("Restart"));

			TextBoxRestart->Font.Size = 16;
			TextBoxRestart->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonRestart->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnRestartButtonClicked);
}

void UTDPauseMenuWidget::InitButtonExit() {
	Panel->AddChild(ButtonExit);
	ButtonExit->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.f);

	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonExit->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetAnchors(FAnchors(0.45f, 0.56f));
	}

	HorizontalBoxExit = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (HorizontalBoxExit) {
		ButtonExit->AddChild(HorizontalBoxExit);

		ImageButtonExit = WidgetTree->ConstructWidget<UImage>();
		if (ImageButtonExit) {
			HorizontalBoxExit->AddChild(ImageButtonExit);

			ImageButtonExit->SetBrushFromTexture(TextureButton);
			ImageButtonExit->SetRenderScale(FVector2D(1.5, 3));
			ImageButtonExit->SetRenderTranslation(FVector2D(24, 25));
		}

		TextBoxExit = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextBoxExit) {
			HorizontalBoxExit->AddChild(TextBoxExit);

			TextBoxExit->SetRenderTranslation(FVector2D(55, 25));
			TextBoxExit->SetVisibility(ESlateVisibility::Visible);

			TextBoxExit->SetText(FText::FromString("Exit"));
			TextBoxExit->Font.Size = 16;
			TextBoxExit->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonExit->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnExitButtonClicked);
}

void UTDPauseMenuWidget::OnContinueButtonClicked(){
	ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->ClosePauseMenu(0);
}

void UTDPauseMenuWidget::OnRestartButtonClicked(){
	ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->ClosePauseMenu(1);
}

void UTDPauseMenuWidget::OnExitButtonClicked(){
	ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->ClosePauseMenu(2);
}

