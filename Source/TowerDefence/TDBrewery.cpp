// Fill out your copyright notice in the Description page of Project Settings.


#include "TDBrewery.h"

// Sets default values
ATDBrewery::ATDBrewery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshBrewery = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBrewery"));
	if (StaticMeshBrewery) {
		SetRootComponent(StaticMeshBrewery);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/Sm_TD_Brewery_01.Sm_TD_Brewery_01'"));
		if (StaticMeshAsset.Succeeded()) {
			StaticMeshBrewery->SetStaticMesh(StaticMeshAsset.Object);
			StaticMeshBrewery->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
		}
	}

	BoxComponentCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	if (BoxComponentCollision) {
		BoxComponentCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		BoxComponentCollision->SetRelativeLocation(FVector(0.0f, 100.0f, 20.0f));
		BoxComponentCollision->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));		
	}

	HealthPoints = 100.0f;
}

// Called when the game starts or when spawned
void ATDBrewery::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDBrewery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATDBrewery::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	HealthPoints -= DamageAmount;

	if (HealthPoints <= 0) {
		ATowerDefenceGameModeBase* GameMode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) {
			GameMode->BreweryDestroyed();
		}
	}
	return 0.0f;
}

