// Fill out your copyright notice in the Description page of Project Settings.


#include "TDBuildingsMenuWidget.h"
#include "TDEmptyTyrret.h"

UTDBuildingsMenuWidget::UTDBuildingsMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> BorderImageAsset(TEXT("/Game/UI/MainMenu/BorderImage"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> FlameImageAsset(TEXT("/Game/UI/HUD/Actions/Buildings/FlamethrowerImage"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> CannonImageAsset(TEXT("/Game/UI/HUD/Actions/Buildings/CannonImage"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrossbowImageAsset(TEXT("/Game/UI/HUD/Actions/Buildings/CrossbowImage"));
	
	TextureBorder = BorderImageAsset.Object;
	TextureFlame = FlameImageAsset.Object;
	TextureCannon = CannonImageAsset.Object;
	TextureCrossbow = CrossbowImageAsset.Object;
}

bool UTDBuildingsMenuWidget::Initialize(){
	Super::Initialize();

	if (WidgetTree){
		Panel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Panel"));

		if (Panel){
			WidgetTree->RootWidget = Panel;
			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Panel->Slot);
			if (PanelSlot) {
				PanelSlot->SetAnchors(FAnchors(0.0, 0.0, 1.f, 1.f));
				PanelSlot->SetOffsets(FMargin(0.0f, 0.0f));				
			}

			ImageBorder = WidgetTree->ConstructWidget<UImage>();
			if (ImageBorder){
				Panel->AddChild(ImageBorder);
				ImageBorder->SetBrushFromTexture(TextureBorder);
				
				UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(ImageBorder->Slot);				
				if (slot) {
					slot->SetAnchors(FAnchors(.83f, .885f));
					slot->SetSize(FVector2D(330, 128));					
				}				
			}	
			
			ButtonFlameTurret = WidgetTree->ConstructWidget<UButton>();
			if (ButtonFlameTurret){
				InitButtonFlame();
			}

			ButtonCannonTurret = WidgetTree->ConstructWidget<UButton>();
			if (ButtonCannonTurret) {
				InitButtonCannon();
			}

			ButtonCrossbowTurret = WidgetTree->ConstructWidget<UButton>();
			if (ButtonCrossbowTurret) {
				InitButtonCrossbow();
			}

		}
	}
	
	return true;
}

void UTDBuildingsMenuWidget::InitButtonFlame() {
	Panel->AddChild(ButtonFlameTurret);

	ButtonFlameTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonFlameTurret->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetSize(FVector2D(100, 100));
		ButtonSlot->SetAnchors(FAnchors(0.84, 0.9));
	}

	CanvasPanelFlame = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (CanvasPanelFlame) {
		ButtonFlameTurret->AddChild(CanvasPanelFlame);

		ImageFlameTurret = WidgetTree->ConstructWidget<UImage>();
		if (ImageFlameTurret) {
			CanvasPanelFlame->AddChild(ImageFlameTurret);

			ImageFlameTurret->SetBrushFromTexture(TextureFlame);
			ImageFlameTurret->SetRenderScale(FVector2D(0.9, 3.2));
			ImageFlameTurret->SetRenderTranslation(FVector2D(-5, 0));
		}

		TextFlameCost = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextFlameCost) {
			CanvasPanelFlame->AddChild(TextFlameCost);

			TextFlameCost->SetVisibility(ESlateVisibility::Visible);
			TextFlameCost->SetRenderTranslation(FVector2D(35.0f, 40.0f));
			TextFlameCost->SetText(FText::FromString(FString::FromInt(TurretsCost::FlamethrowerTurretCost)));

			TextFlameCost->Font.Size = 12;
			TextFlameCost->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonFlameTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnFlameButtonCLicked);
}

void UTDBuildingsMenuWidget::InitButtonCannon(){
	Panel->AddChild(ButtonCannonTurret);

	ButtonCannonTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonCannonTurret->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetSize(FVector2D(100, 100));
		ButtonSlot->SetAnchors(FAnchors(0.885, 0.9));
	}

	CanvasPanelCannon = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (CanvasPanelCannon) {
		ButtonCannonTurret->AddChild(CanvasPanelCannon);

		ImageCanonTurret = WidgetTree->ConstructWidget<UImage>();
		if (ImageCanonTurret) {
			CanvasPanelCannon->AddChild(ImageCanonTurret);

			ImageCanonTurret->SetBrushFromTexture(TextureCannon);
			ImageCanonTurret->SetRenderScale(FVector2D(0.9, 3.2));
			ImageCanonTurret->SetRenderTranslation(FVector2D(0, 0));
		}

		TextCannonCost = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextCannonCost) {
			CanvasPanelCannon->AddChild(TextCannonCost);

			TextCannonCost->SetVisibility(ESlateVisibility::Visible);
			TextCannonCost->SetRenderTranslation(FVector2D(35.0f, 40.0f));
			TextCannonCost->SetText(FText::FromString(FString::FromInt(TurretsCost::CannonTurretCost)));

			TextCannonCost->Font.Size = 12;
			TextCannonCost->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonCannonTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnCannonButtonClicked);
}

void UTDBuildingsMenuWidget::InitButtonCrossbow(){
	Panel->AddChild(ButtonCrossbowTurret);

	ButtonCrossbowTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
	UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonCrossbowTurret->Slot);
	if (ButtonSlot) {
		ButtonSlot->SetSize(FVector2D(100, 100));
		ButtonSlot->SetAnchors(FAnchors(0.93, 0.9));
	}

	CanvasPanelCrossbow = WidgetTree->ConstructWidget<UCanvasPanel>();
	if (CanvasPanelCrossbow) {
		ButtonCrossbowTurret->AddChild(CanvasPanelCrossbow);

		ImageCrossbowTurret = WidgetTree->ConstructWidget<UImage>();
		if (ImageCrossbowTurret) {
			CanvasPanelCrossbow->AddChild(ImageCrossbowTurret);

			ImageCrossbowTurret->SetBrushFromTexture(TextureCrossbow);
			ImageCrossbowTurret->SetRenderScale(FVector2D(0.9, 3.2));
			ImageCrossbowTurret->SetRenderTranslation(FVector2D(5, 0));
		}

		TextCrossbowCost = WidgetTree->ConstructWidget<UTextBlock>();
		if (TextCrossbowCost) {
			CanvasPanelCrossbow->AddChild(TextCrossbowCost);

			TextCrossbowCost->SetVisibility(ESlateVisibility::Visible);
			TextCrossbowCost->SetRenderTranslation(FVector2D(35.0f, 40.0f));
			TextCrossbowCost->SetText(FText::FromString(FString::FromInt(TurretsCost::CrossbowTurretCost)));

			TextCrossbowCost->Font.Size = 12;
			TextCrossbowCost->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.97f, 0.16f, 1.0f)));
		}
	}

	ButtonCrossbowTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnCrossbowButtonClicked);
}

void UTDBuildingsMenuWidget::SetCurrentTurret(AActor * Turret) {
	CurrentTurret = Turret;
}

void UTDBuildingsMenuWidget::OnFlameButtonCLicked() {
	ButtonClicked(TurretsTypes::FlamethrowerTurret);
}

void UTDBuildingsMenuWidget::OnCannonButtonClicked() {
	ButtonClicked(TurretsTypes::CannonTurret);
}

void UTDBuildingsMenuWidget::OnCrossbowButtonClicked() {
	ButtonClicked(TurretsTypes::CrossbowTurret);
}



void UTDBuildingsMenuWidget::ButtonClicked(TurretsTypes Type){	
	ATDEmptyTyrret* Turret = Cast<ATDEmptyTyrret>(CurrentTurret);	
	if (Turret){
		if (Turret->StartConstruction(Type)) {
			Turret->Destroy();
			CurrentTurret = nullptr;
		}
	}
}