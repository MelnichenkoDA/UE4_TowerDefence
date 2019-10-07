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
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshMidAsset(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TD_Projectile_Arrow.SM_TD_Projectile_Arrow'"));
		if (StaticMeshMidAsset.Succeeded()) {
			StaticMeshMidArrow->SetStaticMesh(StaticMeshMidAsset.Object);

		}
	}

	StaticMeshLeftArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLeftArrow"));
	if (StaticMeshLeftArrow) {
		StaticMeshLeftArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshLeftAsset(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TD_Projectile_Arrow.SM_TD_Projectile_Arrow'"));
		if (StaticMeshLeftAsset.Succeeded()) {
			StaticMeshLeftArrow->SetStaticMesh(StaticMeshLeftAsset.Object);
			StaticMeshLeftArrow->SetRelativeLocation(FVector(-60.0f, 0.0f, -20.0f));

		}
	}

	StaticMeshRightArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshRightArrow"));
	if (StaticMeshRightArrow) {
		StaticMeshRightArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRightAsset(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TD_Projectile_Arrow.SM_TD_Projectile_Arrow'"));
		if (StaticMeshRightAsset.Succeeded()) {
			StaticMeshRightArrow->SetStaticMesh(StaticMeshRightAsset.Object);
			StaticMeshRightArrow->SetRelativeLocation(FVector(60.0f, 0.0f, -20.0f));
		}
	}

	LifeTime = 5.0f;

	MovementSpeed = 350.f;
}

void ATDCrossbowArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATDCrossbowArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;

	if (LifeTime > 0) {
		FVector Direction = GetActorRotation().Vector();
		FVector NewLocation = GetActorLocation();
		switch (int(Direction.X)) {
		case 0:
			Direction.X = Direction.Y;
			Direction.Y = 0.0f;

			NewLocation -= Direction * MovementSpeed * DeltaTime;
			break;
		default:
			Direction.Y = Direction.X;
			Direction.X = 0.0f;

			NewLocation += Direction * MovementSpeed * DeltaTime;
			break;
		}
		SetActorLocation(NewLocation);
	} else {
		Destroy();
	}
}

