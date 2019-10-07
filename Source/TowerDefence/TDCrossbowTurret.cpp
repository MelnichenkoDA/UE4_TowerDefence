// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCrossbowTurret.h"

// Sets default values
ATDCrossbowTurret::ATDCrossbowTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshFoundation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshFoundation"));
	if (StaticMeshFoundation) {
		SetRootComponent(StaticMeshFoundation);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/ArbalesTower_StaticElement.ArbalesTower_StaticElement'"));
		if (StaticMeshAsset.Succeeded()) {
			StaticMeshFoundation->SetStaticMesh(StaticMeshAsset.Object);
			StaticMeshFoundation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			StaticMeshFoundation->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

	SkeletalMeshCrossbow = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshCrossbow"));
	if (SkeletalMeshCrossbow) {
		SkeletalMeshCrossbow->AttachTo(RootComponent);
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/Assets/Meshes/ArbalestTower_SkelMesh.ArbalestTower_SkelMesh'"));
		if (SkeletalMeshAsset.Succeeded()) {
			SkeletalMeshCrossbow->SetSkeletalMesh(SkeletalMeshAsset.Object);
			SkeletalMeshCrossbow->SetRelativeLocation(FVector(0.0f, -10.0f, 110.0f));
			SkeletalMeshCrossbow->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		}
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationAsset(TEXT("AnimSequence'/Game/Assets/Animations/ArbalestTower_Shooting.ArbalestTower_Shooting'"));
	if (AnimationAsset.Succeeded()) {
		AnimationShooting = AnimationAsset.Object;		
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

	ReloadMaxTime = 5.0f;

	ReloadCurrentTime = 0.0f;

	Damage = 5.0f;

}

// Called when the game starts or when spawned
void ATDCrossbowTurret::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ATDCrossbowTurret::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	ReloadCurrentTime -= DeltaTime;
	if (ReloadCurrentTime <= 0) {		
		FVector SpawnPlace = GetActorLocation() + GetActorLocation().ForwardVector * 200.0f;
		SpawnPlace.Z += 120;		
		FRotator SpawnRotation = GetActorRotation();	
		SpawnRotation.Roll = 90.0f;
		
		ATDCrossbowArrow* Arrow = GetWorld()->SpawnActor<ATDCrossbowArrow>(SpawnPlace, SpawnRotation);
		ReloadCurrentTime = ReloadMaxTime;
	}

}

