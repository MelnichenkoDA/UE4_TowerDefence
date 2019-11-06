// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCannonBall.h"

// Sets default values
ATDCannonBall::ATDCannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBall"));
	if (StaticMeshBall) {
		SetRootComponent(StaticMeshBall);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshBall(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TD_Projectile_CannonBall.SM_TD_Projectile_CannonBall'"));
		if (MeshBall.Succeeded()) {
			StaticMeshBall->SetStaticMesh(MeshBall.Object);
			StaticMeshBall->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));			
		}
	}

	SphereComponentCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	if (SphereComponentCollision) {
		SphereComponentCollision->AttachTo(StaticMeshBall);
		SphereComponentCollision->OnComponentBeginOverlap.AddDynamic(this, &ATDCannonBall::OnBeginOverlap);
	}

	ParticleSystemTail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleTail"));
	if (ParticleSystemTail) {
		ParticleSystemTail->AttachTo(RootComponent);
		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleTailAsset(TEXT("ParticleSystem'/Game/Environment/Effects/particles/Arbalest_Projectile.Arbalest_Projectile'"));
		if (ParticleTailAsset.Succeeded()) {
			ParticleSystemTail->SetTemplate(ParticleTailAsset.Object);
			ParticleSystemTail->SetRelativeLocation(FVector(0.f, 0.0f, 0.0f));
			ParticleSystemTail->SetRelativeScale3D(FVector(3.0f, 2.0f, 2.0f));
		}
	}
	
	MovementSpeed = 450.f;

	LifeTime = 5.f;
}

// Called when the game starts or when spawned
void ATDCannonBall::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATDCannonBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (LifeTime >= 0) {
		LifeTime -= DeltaTime;

		SetActorLocation(GetActorLocation() + DeltaTime * MovementSpeed * DirectionVector);
	} else {
		Destroy();
	}

}

void ATDCannonBall::Initialize(const FVector& TargetPosition, const float& Damage) {
	DirectionVector = TargetPosition - StaticMeshBall->GetComponentLocation();
	FRotator Rot = FRotationMatrix::MakeFromX(DirectionVector).Rotator();

	DirectionVector.Normalize();

	SetActorRotation(Rot);

	this->TargetPosition = TargetPosition;
	this->Damage = Damage;
}

void ATDCannonBall::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != nullptr && OtherActor->GetClass()->GetName() == "TDDwarf") {
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = UTDDamageTypeCannon::StaticClass();
		OtherActor->TakeDamage(Damage, DamageEvent, nullptr, nullptr);
		Destroy();
	}	
}

