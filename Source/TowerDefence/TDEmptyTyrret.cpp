// Fill out your copyright notice in the Description page of Project Settings.


#include "TDEmptyTyrret.h"
#include "TDBuildingsManager.h"

AActor* ATDEmptyTyrret::Manager;

// Sets default values
ATDEmptyTyrret::ATDEmptyTyrret(){
	
	PrimaryActorTick.bCanEverTick = true;

	StoneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoneMesh"));
	RootComponent = StoneMeshComponent;

	TurretMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StoneMeshVisual(TEXT("StaticMesh'/Game/Assets/Meshes/RTS_Env_Cliffs_CliffWall_Box.RTS_Env_Cliffs_CliffWall_Box'"));
	if (StoneMeshVisual.Succeeded()) {
		StoneMeshComponent->SetStaticMesh(StoneMeshVisual.Object);
		StoneMeshComponent->OnClicked.AddDynamic(this, &ATDEmptyTyrret::OnMouseClick);
	}	

	TurretMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	TurretMeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATDEmptyTyrret::BeginPlay(){
	Super::BeginPlay();
	
	if (!Manager) {
		for (TActorIterator<ATDBuildingsManager> Actoritr(GetWorld()); Actoritr; ++Actoritr) {
			Manager = *Actoritr;
		}
	}
	
}

// Called every frame
void ATDEmptyTyrret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATDEmptyTyrret::OnMouseClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed) {
	ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD) {
		HUD->ShowConstructionMenu(Cast<AActor>(this));
	}
}

bool ATDEmptyTyrret::StartConstruction(TurretsTypes Type){
	ATDBuildingsManager* BuildingsManager = static_cast<ATDBuildingsManager*>(Manager);
	
	if (BuildingsManager->CheckConstruct(Type)) {
		BuildingsManager->InitConstruction(Type, GetTransform());
		ATDHUD* HUD = Cast<ATDHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD) {			
			HUD->CloseCurrentMenu();
			return true;
		}
	}
	return false;
}

