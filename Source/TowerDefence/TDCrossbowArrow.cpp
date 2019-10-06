// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCrossbowArrow.h"

// Sets default values
ATDCrossbowArrow::ATDCrossbowArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshMidArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMiddleArrow"));
	if (StaticMeshMidArrow) {
		SetRootComponent(StaticMeshMidArrow);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TD_Projectile_Arrow.SM_TD_Projectile_Arrow'"));
		if (StaticMeshAsset.Succeeded()) {
			StaticMeshMidArrow->SetStaticMesh(StaticMeshAsset.Object);

		}
	}

	/*if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "1!!");
	}*/

}

// Called when the game starts or when spawned
void ATDCrossbowArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDCrossbowArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

