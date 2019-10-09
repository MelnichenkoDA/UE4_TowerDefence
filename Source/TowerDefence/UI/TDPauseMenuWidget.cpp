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

			ImageButtonContinue = WidgetTree->ConstructWidget<UImage>();
			if (ImageButtonContinue) {
				ImageButtonContinue->SetBrushFromTexture(TextureButton);
			} 

			ImageButtonRestart = WidgetTree->ConstructWidget<UImage>();
			if (ImageButtonRestart) {
				ImageButtonRestart->SetBrushFromTexture(TextureButton);
			}

			ImageButtonExit = WidgetTree->ConstructWidget<UImage>();
			if (ImageButtonExit) {
				ImageButtonExit->SetBrushFromTexture(TextureButton);
			}

			ButtonContinue = WidgetTree->ConstructWidget<UButton>();
			if (ButtonContinue) {
				Panel->AddChild(ButtonContinue);

				//ButtonContinue->SetRenderTranslation(FVector2D(GSystemResolution.ResX * 0.45, GSystemResolution.ResY * 0.45));
				ButtonContinue->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);

				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonContinue->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(150, 100));
					ButtonSlot->SetAnchors(FAnchors(0.45f, 0.4f));
				}

				if (ImageButtonContinue) {
					ButtonContinue->AddChild(ImageButtonContinue);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageButtonContinue->Slot);
					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}

				ButtonContinue->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnContinueButtonClicked);
			} 

			ButtonRestart = WidgetTree->ConstructWidget<UButton>();
			if (ButtonRestart) {
				Panel->AddChild(ButtonRestart);
				ButtonRestart->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);

				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonRestart->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(150, 100));
					ButtonSlot->SetAnchors(FAnchors(0.45f, 0.48f));
				}

				if (ImageButtonRestart) {
					ButtonRestart->AddChild(ImageButtonRestart);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageButtonRestart->Slot);
					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}
				ButtonRestart->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnRestartButtonClicked);
			}

			ButtonExit = WidgetTree->ConstructWidget<UButton>();
			if (ButtonExit) {
				Panel->AddChild(ButtonExit);			

				ButtonExit->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.f);

				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonExit->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(150, 100));
					ButtonSlot->SetAnchors(FAnchors(0.45f, 0.56f));
				}

				if (ImageButtonExit) {
					ButtonExit->AddChild(ImageButtonExit);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageButtonExit->Slot);
					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}

				ButtonExit->OnClicked.AddDynamic(this, &UTDPauseMenuWidget::OnExitButtonClicked);
			}
		}
	}

	return true;
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
