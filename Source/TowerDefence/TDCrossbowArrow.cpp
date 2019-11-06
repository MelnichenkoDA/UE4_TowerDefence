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

	CollisionCompoment = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	if (CollisionCompoment) {
		CollisionCompoment->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CollisionCompoment->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
		CollisionCompoment->SetWorldScale3D(FVector(2.25f, 1.0f, 0.25));
		CollisionCompoment->OnComponentBeginOverlap.AddDynamic(this, &ATDCrossbowArrow::OnBeginOverlap);
	}

	LifeTime = 0.0f;

	MovementSpeed = 0.0f;

	Damage = 0.0f;
}

void ATDCrossbowArrow::BeginPlay(){
	Super::BeginPlay();	
}

void ATDCrossbowArrow::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;

	if (LifeTime > 0) {
		FVector Direction = GetActorRotation().Vector();

		Swap(Direction.X, Direction.Y);

		if (Direction.X) {
			Direction.X *= -1;
		}

		FVector NewLocation = GetActorLocation() + DeltaTime * Direction * MovementSpeed;		

		SetActorLocation(NewLocation);
	} else {
		Destroy();
	}
}

void ATDCrossbowArrow::Initialize(const float& Damage, const float& Speed, const float& LifeTime){
	this->Damage = Damage;
	this->MovementSpeed = Speed;
	this->LifeTime = LifeTime;
}

void ATDCrossbowArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (OtherActor->GetClass()->GetName() == "TDDwarf") {
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = UTDDamageTypeArrow::StaticClass();
		OtherActor->TakeDamage(Damage, DamageEvent, nullptr, nullptr);
	}
}

