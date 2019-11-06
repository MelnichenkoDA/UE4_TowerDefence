// Fill out your copyright notice in the Description page of Project Settings.


#include "TDFlamethrowerTurret.h"

// Sets default values
ATDFlamethrowerTurret::ATDFlamethrowerTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TurretMesh(TEXT("SkeletalMesh'/Game/Assets/Meshes/FlameTower_SkelMesh.FlameTower_SkelMesh'"));
	if (TurretMesh.Succeeded()) {
		SetRootComponent(TurretMeshComponent);
		TurretMeshComponent->SetSkeletalMesh(TurretMesh.Object);
	}

	FlameMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlameMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FlameMeshVisual(TEXT("StaticMesh'/Game/Assets/Effects/Meshes/S_plane.S_plane'"));
	if (FlameMeshVisual.Succeeded()) {
		FlameMeshComponent->SetStaticMesh(FlameMeshVisual.Object);
		FlameMeshComponent->AttachTo(RootComponent);
		FlameMeshComponent->SetVisibility(false);
		FlameMeshComponent->SetRelativeLocation(FVector(0.0f, 400.0f, 50.0f));
		FlameMeshComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		FlameMeshComponent->SetRelativeScale3D(FVector(1.0f, 2.5f, 1.0f));
	}

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	if (CollisionComponent) {
		CollisionComponent->AttachTo(RootComponent);
		CollisionComponent->SetGenerateOverlapEvents(false);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATDFlamethrowerTurret::OnFlameBeginOverlap);	
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATDFlamethrowerTurret::OnFlameEndOverlap);
		CollisionComponent->SetRelativeLocation(FVector(0.0f, 400.0f, 50.0f));
		CollisionComponent->SetRelativeScale3D(FVector(3.5, 3.5, 1.0f));
	}

	ParticleComponentCreation = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleCreation"));
	if (ParticleComponentCreation) {
		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/Environment/Effects/particles/P_building_creation_01.P_building_creation_01'"));
		if (ParticleAsset.Succeeded()) {
			ParticleComponentCreation->SetTemplate(ParticleAsset.Object);
			ParticleComponentCreation->AttachTo(RootComponent);
			ParticleComponentCreation->bAutoActivate = true;
		}
	}

	ConstructionBarWidget = CreateWidget<UTDConstructionBarWidget>(GetWorld(), UTDConstructionBarWidget::StaticClass());

	Damage = 1.5f;

	ConstructionTimer = 0.0f;

	bConstructed = false;
}

void ATDFlamethrowerTurret::Initialise(const float& Timer) {	
	ConstructionTimer = Timer;

	ConstructionBarWidget->AddToViewport();
	ConstructionBarWidget->SetPositionAndTime(GetActorLocation(), &ConstructionTimer);
}

// Called when the game starts or when spawned
void ATDFlamethrowerTurret::BeginPlay(){
	Super::BeginPlay();	
}

// Called every frame
void ATDFlamethrowerTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bConstructed && ConstructionTimer > 0.0) {
		ConstructionTimer -= DeltaTime;
		if (ConstructionTimer <= 0) {
			bConstructed = true;
		}
	}

	if (bConstructed) {
		if (ConstructionBarWidget->IsInViewport()) {
			ConstructionBarWidget->RemoveFromViewport();
			FlameMeshComponent->SetVisibility(true);
			CollisionComponent->SetGenerateOverlapEvents(true);
		}
	}
}

void ATDFlamethrowerTurret::OnFlameBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UTDDamageTypeFlame::StaticClass();
	if (OtherActor) {
		OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
	}
}

void ATDFlamethrowerTurret::OnFlameEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UTDDamageTypeFlame::StaticClass();
	if (OtherActor) {
		OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
	}
}