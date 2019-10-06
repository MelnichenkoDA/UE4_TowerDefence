// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMainWidget.h"
#include "TDHUD.h"

UTDMainWidget::UTDMainWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> BorderImage(TEXT("/Game/UI/MainMenu/BorderImage"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PauseImage(TEXT("/Game/UI/HUD/Actions/ActionPause"));

	TextureBorder = BorderImage.Object;
	TexturePauseButton = PauseImage.Object;
}

void UTDMainWidget::NativeConstruct() {
	Super::NativeConstruct();
	
}

bool UTDMainWidget::Initialize() {
	Super::Initialize();
	
	if (WidgetTree) {
		Panel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Panel"));

		if (Panel) {
			WidgetTree->RootWidget = Panel;
			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Panel->Slot);
			if (PanelSlot) {
				PanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.f, 1.f));
				PanelSlot->SetOffsets(FMargin(0.0f, 0.0f));
			}										

			ImageGoldBorder = WidgetTree->ConstructWidget<UImage>();
			if (ImageGoldBorder) {
				Panel->AddChild(ImageGoldBorder);
				ImageGoldBorder->SetBrushFromTexture(TextureBorder);
				ImageGoldBorder->SetRenderTranslation(FVector2D(0.0f, 0.0f));
			}			
			
			TextBoxGold = WidgetTree->ConstructWidget<UTextBlock>();
			if (TextBoxGold) {
				Panel->AddChild(TextBoxGold);
				TextBoxGold->SetRenderTranslation(FVector2D(10.0f, 5.0f));
				TextBoxGold->SetVisibility(ESlateVisibility::Visible);

				TextBoxGold->SetText(FText::FromString("Gold : 0"));
				TextBoxGold->Font.Size = 12;
				TextBoxGold->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
			}
			
			ImageWaveBorder = WidgetTree->ConstructWidget<UImage>();
			if (ImageWaveBorder) {
				Panel->AddChild(ImageWaveBorder);
				ImageWaveBorder->SetBrushFromTexture(TextureBorder);
				ImageWaveBorder->SetRenderTranslation(FVector2D(GSystemResolution.ResX * 0.45, 0));
			}
			
			TextBoxCurrentWave = WidgetTree->ConstructWidget<UTextBlock>();
			if (TextBoxCurrentWave) { 
				Panel->AddChild(TextBoxCurrentWave);
				TextBoxCurrentWave->SetRenderTranslation(FVector2D(GSystemResolution.ResX * 0.45 + 10.0f, 5.f));
				TextBoxCurrentWave->SetVisibility(ESlateVisibility::Visible);
				
				TextBoxCurrentWave->SetText(FText::FromString("Wave : 0"));
				TextBoxCurrentWave->Font.Size = 12;
				TextBoxCurrentWave->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
			}

			ButtonMenu = WidgetTree->ConstructWidget<UButton>();
			if (ButtonMenu) {
				Panel->AddChild(ButtonMenu);
				
				ButtonMenu->SetRenderTranslation(FVector2D(GSystemResolution.ResX * 0.9, 5.0f));
				ButtonMenu->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
				
				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonMenu->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(50, 50));						
				}				
				
				ImagePause = WidgetTree->ConstructWidget<UImage>();
				if (ImagePause) {
					ButtonMenu->AddChild(ImagePause);
					ImagePause->SetBrushFromTexture(TexturePauseButton);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImagePause->Slot);
					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}
				

				ButtonMenu->OnClicked.AddDynamic(this, &UTDMainWidget::OnMenuButtonClick);
			}
		}		
	}

	return true;
}

void UTDMainWidget::OnMenuButtonClick() {
	ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->ShowPauseMenu();
}

void UTDMainWidget::SetGold(const unsigned & Gold) {	
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Gold));
	}
	TextBoxGold->SetText(FText::FromString(FString("Gold : ") + FString::FromInt(Gold)));		
}

void UTDMainWidget::SetWave(const unsigned & Wave) {
	TextBoxCurrentWave->SetText(FText::FromString(FString::FromInt(Wave)));
}