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
				ImageGoldBorder->SetRenderScale(FVector2D(1.5, 1));
				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ImageGoldBorder->Slot);
				if (Slot) {
					Slot->SetAnchors(FAnchors(0.0f, 0.0f));
				}
			}			
			
			TextBoxGold = WidgetTree->ConstructWidget<UTextBlock>();
			if (TextBoxGold) {
				Panel->AddChild(TextBoxGold);
				TextBoxGold->SetRenderTranslation(FVector2D(10.0f, 5.0f));
				TextBoxGold->SetVisibility(ESlateVisibility::Visible);

				TextBoxGold->SetText(FText::FromString("Gold : 0"));
				TextBoxGold->Font.Size = 16;
				TextBoxGold->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
			}
			
			ImageWaveBorder = WidgetTree->ConstructWidget<UImage>();
			if (ImageWaveBorder) {
				Panel->AddChild(ImageWaveBorder);
				ImageWaveBorder->SetBrushFromTexture(TextureBorder);
				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ImageWaveBorder->Slot);
				if (Slot) {
					Slot->SetAnchors(FAnchors(0.5f, 0.0f));
				}
			}
			
			TextBoxCurrentWave = WidgetTree->ConstructWidget<UTextBlock>();
			if (TextBoxCurrentWave) { 
				Panel->AddChild(TextBoxCurrentWave);
				TextBoxCurrentWave->SetVisibility(ESlateVisibility::Visible);
				
				TextBoxCurrentWave->SetText(FText::FromString("Wave : 0"));
				TextBoxCurrentWave->Font.Size = 16;
				TextBoxCurrentWave->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(TextBoxCurrentWave->Slot);
				if (Slot) {
					Slot->SetAnchors(FAnchors(0.505f, 0.002f));					
				}
			}

			ButtonMenu = WidgetTree->ConstructWidget<UButton>();
			if (ButtonMenu) {
				Panel->AddChild(ButtonMenu);				
				
				ButtonMenu->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
				
				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonMenu->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(100, 100));			
					ButtonSlot->SetAnchors(FAnchors(0.95, 0.0f));
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

			GameEndMessage = WidgetTree->ConstructWidget<UTextBlock>();
			if (GameEndMessage) {
				Panel->AddChild(GameEndMessage);
				GameEndMessage->SetVisibility(ESlateVisibility::Hidden);

				GameEndMessage->SetText(FText::FromString(""));
				GameEndMessage->Font.Size = 24;
				GameEndMessage->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(GameEndMessage->Slot);
				if (Slot) {
					Slot->SetAnchors(FAnchors(0.46f, 0.35));
				}
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
	TextBoxGold->SetText(FText::FromString(FString("Gold : ") + FString::FromInt(Gold)));		
}

void UTDMainWidget::SetWave(const unsigned & Wave) {
	TextBoxCurrentWave->SetText(FText::FromString(FString("Wave : ") + FString::FromInt(Wave)));
}

void UTDMainWidget::ShowEndMessage(const FString& Message){
	GameEndMessage->SetVisibility(ESlateVisibility::Visible);

	GameEndMessage->SetText(FText::FromString(Message));
}
