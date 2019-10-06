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
				Panel->AddChild(ButtonFlameTurret);

				ButtonFlameTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);				
				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonFlameTurret->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(100, 100));
					ButtonSlot->SetAnchors(FAnchors(0.84, 0.9));
				}

				ImageFlameTurret = WidgetTree->ConstructWidget<UImage>();
				if (ImageFlameTurret) {
					ImageFlameTurret->SetBrushFromTexture(TextureFlame);
					ButtonFlameTurret->AddChild(ImageFlameTurret);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageFlameTurret->Slot);

					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}

				ButtonFlameTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnFlameButtonCLicked);				
			}

			ButtonCannonTurret = WidgetTree->ConstructWidget<UButton>();
			if (ButtonCannonTurret) {
				Panel->AddChild(ButtonCannonTurret);

				ButtonCannonTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);				
				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonCannonTurret->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(100, 100));
					ButtonSlot->SetAnchors(FAnchors(.89, .9));
				}

				ImageCanonTurret = WidgetTree->ConstructWidget<UImage>();
				if (ImageCanonTurret) {
					ImageCanonTurret->SetBrushFromTexture(TextureCannon);
					ButtonCannonTurret->AddChild(ImageCanonTurret);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageCanonTurret->Slot);

					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}

				ButtonCannonTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnCannonButtonClicked);
			}

			ButtonCrossbowTurret = WidgetTree->ConstructWidget<UButton>();
			if (ButtonCrossbowTurret) {
				Panel->AddChild(ButtonCrossbowTurret);
				ButtonCrossbowTurret->BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);

				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(ButtonCrossbowTurret->Slot);
				if (ButtonSlot) {
					ButtonSlot->SetSize(FVector2D(100, 100));
					ButtonSlot->SetAnchors(FAnchors(.94, .9));
				}

				ImageCrossbowTurret = WidgetTree->ConstructWidget<UImage>();
				if (ImageCrossbowTurret) {
					ImageCrossbowTurret->SetBrushFromTexture(TextureCrossbow);
					ButtonCrossbowTurret->AddChild(ImageCrossbowTurret);
					UButtonSlot* ImageSlot = Cast<UButtonSlot>(ImageCrossbowTurret->Slot);

					if (ImageSlot) {
						ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						ImageSlot->SetPadding(FMargin(0));
					}
				}

				ButtonCrossbowTurret->OnClicked.AddDynamic(this, &UTDBuildingsMenuWidget::OnCrossbowButtonClicked);
			}

		}
	}
	
	return true;
}

void UTDBuildingsMenuWidget::SetCurrentTurret(AActor * Turret) {
	CurrentTurret = Turret;
	if (Turret == nullptr && GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WIDGET"));
	}
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