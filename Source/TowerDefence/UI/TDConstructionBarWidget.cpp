// Fill out your copyright notice in the Description page of Project Settings.


#include "TDConstructionBarWidget.h"

UTDConstructionBarWidget::UTDConstructionBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	 
}

bool UTDConstructionBarWidget::Initialize(){
	Super::Initialize();

	if (WidgetTree) {
		Panel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Panel"));
		if (Panel) {
			WidgetTree->RootWidget = Panel;
			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Panel->Slot);
			if (PanelSlot) {
				PanelSlot->SetAnchors(FAnchors(0.0, 0.0, 1.f, 1.f));
				PanelSlot->SetOffsets(FMargin(0.0f, 0.0f));
			}

			ProgressBar = WidgetTree->ConstructWidget<UProgressBar>();
			if (ProgressBar) {
				Panel->AddChild(ProgressBar);

				ProgressBar->SetVisibility(ESlateVisibility::Hidden);
				ProgressBar->SetFillColorAndOpacity(FLinearColor::Blue);
				ProgressBar->SetPercent(0);
			}

		}
	}

	return true;
}

void UTDConstructionBarWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime){
	if (CurrentTime <= 0) {
		*bFinished = true;
		return;
	}
	
	if (!(*bFinished)) {
		CurrentTime -= DeltaTime;	
		
		FVector2D ScreenLocation;
		
		PlayerController->ProjectWorldLocationToScreen(TargetPosition, ScreenLocation);	

		ProgressBar->SetPercent(1 - CurrentTime / MaxTime);

		BarSlot->SetPosition(ScreenLocation);

	}
}

void UTDConstructionBarWidget::SetPositionAndTime(const FVector& Position, const float& Time, bool* bConstructed){
	TargetPosition = Position;
	MaxTime = CurrentTime = Time;
	
	BarSlot = Cast<UCanvasPanelSlot>(ProgressBar->Slot);
	PlayerController = Cast<const APlayerController>(GetWorld()->GetFirstPlayerController());
	if (BarSlot && PlayerController) {		
		ProgressBar->SetVisibility(ESlateVisibility::Visible);		
		BarSlot->SetAnchors(FAnchors(0.0f, 0.0f));
	}
	
	bFinished = bConstructed;
	
}
