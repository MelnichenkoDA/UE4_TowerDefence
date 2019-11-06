// Fill out your copyright notice in the Description page of Project Settings.


#include "TDDwarf.h"

// Sets default values
ATDDwarf::ATDDwarf(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f, true);
	GetCapsuleComponent()->SetCapsuleRadius(45.f, true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATDDwarf::OnCollisionOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationDeathAsset(TEXT("AnimSequence'/Game/Characters/DwarfGrunt/Anims/Death2.Death2'"));
	if (AnimationDeathAsset.Succeeded()) {
		AnimationDeath = AnimationDeathAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationMoveFrdAsset(TEXT("AnimSequence'/Game/Characters/DwarfGrunt/Anims/WalkFwd2.WalkFwd2'"));
	if (AnimationMoveFrdAsset.Succeeded()) {
		AnimationMoveFrd = AnimationMoveFrdAsset.Object;
	}
	
	SkeletalComponent = GetMesh();
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshDwarf(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/DwarfGrunt_R_new.DwarfGrunt_R_new'"));
	if (MeshDwarf.Succeeded()) {
		SkeletalComponent->SetSkeletalMesh(MeshDwarf.Object);
		SkeletalComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	ParticleComponentBurn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleBurn"));
	if (ParticleComponentBurn) {
		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAssetBurn(TEXT("ParticleSystem'/Game/Environment/Effects/particles/P_body_burn_01.P_body_burn_01'"));
		if (ParticleAssetBurn.Succeeded()) {
			ParticleComponentBurn->SetTemplate(ParticleAssetBurn.Object);
		}
		ParticleComponentBurn->SetupAttachment(SkeletalComponent);		
		ParticleComponentBurn->bAutoActivate = false;
		ParticleComponentBurn->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
		ParticleComponentBurn->SetWorldScale3D(FVector(1.5f, 1.5f, 1.0f));
	}
	

	ParticleComponentBlood = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleBlood")); {
		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAssetBlood(TEXT("ParticleSystem'/Game/Environment/Effects/particles/P_blood_splash_02.P_blood_splash_02'"));
		if (ParticleAssetBlood.Succeeded()) {
			ParticleComponentBlood->SetTemplate(ParticleAssetBlood.Object);
		}
		ParticleComponentBlood->SetupAttachment(SkeletalComponent);		
		ParticleComponentBlood->bAutoActivate = false;
	}
	
	Damage = 10.0f;

	HealthPoints = 30;	
	MovementSpeed = 100.0f;

	DestroyingTimer = 5.0f;

	bIsAlive = true;

	CurrentPointIndex = 0;

	ContiniusDamageTimer = 0.0f;
	ContiniusDamage = 0.0f;

	CurrentTarget = nullptr;
}

// Called when the game starts or when spawned
void ATDDwarf::BeginPlay(){
	Super::BeginPlay();
	SkeletalComponent->PlayAnimation(AnimationMoveFrd, true);
}

// Called every frame
void ATDDwarf::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (HealthPoints <= 0 ) {
		if (bIsAlive) {
			bIsAlive = false;	
			SkeletalComponent->PlayAnimation(AnimationDeath, false);
		}
		if (!bIsAlive) {
			if (DestroyingTimer > 0) {
				DestroyingTimer -= DeltaTime;
			} else {
				Destroy();
			}
		}
	} else {
		if (CurrentTarget) {
			FVector NewLocation = GetActorLocation();
			FVector Direction = GetActorRotation().Vector();	

			Swap(Direction.X, Direction.Y);

			if (Direction.X) {
				Direction.X *= -1;
			}
			NewLocation += Direction * MovementSpeed * DeltaTime;
			
			NewLocation.Z = GetActorLocation().Z;
			SetActorLocation(NewLocation);
		}
		
		if (ContiniusDamageTimer > 0) {			
			HealthPoints -= ContiniusDamage * DeltaTime;
			
			ContiniusDamageTimer -= DeltaTime;
			if (ContiniusDamageTimer <= 0){
				ParticleComponentBurn->Deactivate();
			}
		}
	}	
}

float ATDDwarf::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	FString DamageTypeName;
	DamageEvent.DamageTypeClass.Get()->GetName(DamageTypeName);
	if (DamageTypeName == "TDDamageTypeFlame") {	
		UTDDamageTypeFlame* DamageType = Cast<UTDDamageTypeFlame>(DamageEvent.DamageTypeClass.GetDefaultObject());
		if (DamageType) {
			DamageType->InitDamage(ContiniusDamageTimer);
			ContiniusDamage = DamageAmount;
		}
		if (!ParticleComponentBurn->bIsActive) {
			ParticleComponentBurn->Activate();
		}
	}
	if (DamageTypeName == "TDDamageTypeCannon") {
		if (!ParticleComponentBlood->bIsActive) {
			ParticleComponentBlood->Activate();
		}
	}
	if (DamageTypeName == "TDDamageTypeArrow") {
		if (!ParticleComponentBlood->bIsActive) {
			ParticleComponentBlood->Activate();
		}
	}

	HealthPoints -= DamageAmount;

	return 0.0;
}

void ATDDwarf::Initialize(ATDWayPoint* TargetPosition, DwarfType Type){
	CurrentTarget = TargetPosition;
	SetCurrentPoint();

	FVector NewLocation = GetActorLocation();

	switch (Type) {
	case DwarfType::Little : 
		SkeletalComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
		
		NewLocation.Z = 270;
		SetActorLocation(NewLocation);

		SkeletalComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));

		GetCapsuleComponent()->SetCapsuleHalfHeight(34.f, true);
		GetCapsuleComponent()->SetCapsuleRadius(30.f, true);

		Award = DwarfAwardType::LittleAward;
		MovementSpeed = DwarfMovementSpeedType::LittleSpeed;
		HealthPoints = DwarfHealthType::LittleHP;
		Damage = DwarfDamageType::LittleDamage;
		break;
	case DwarfType::Middle :		
		SkeletalComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));

		GetCapsuleComponent()->SetCapsuleHalfHeight(0.44f, true);
		Award = DwarfAwardType::MiddleAward;
		MovementSpeed = DwarfMovementSpeedType::MiddleSpeed;
		HealthPoints = DwarfHealthType::MiddleHP;
		Damage = DwarfDamageType::MiddleDamage;
		break;
	case DwarfType::Big:
		SkeletalComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
		
		NewLocation.Z = 320;
		SetActorLocation(NewLocation);

		SkeletalComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));

		GetCapsuleComponent()->SetCapsuleHalfHeight(90.f, true);
		GetCapsuleComponent()->SetCapsuleRadius(60.f, true);
		
		Award = DwarfAwardType::BigAward;
		MovementSpeed = DwarfMovementSpeedType::BigSpeed;
		HealthPoints = DwarfHealthType::BigHP;
		Damage = DwarfDamageType::BigDamage;
		break;
	}
}

const bool& ATDDwarf::IsAlive(){
	return bIsAlive;
}

void ATDDwarf::OnCollisionOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	if (OtherActor->GetClass()->GetName() == "TDWayPoint") {		
		CurrentTarget = CurrentTarget->GetNextPoint();
		SetCurrentPoint();
	}

	if (OtherActor->GetClass()->GetName() == "TDBrewery") {		
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, nullptr, nullptr);
		Destroy();
	}
}

const unsigned& ATDDwarf::GetAward(){
	return Award;
}


void ATDDwarf::SetCurrentPoint(){
	if (CurrentTarget) {
		FVector Direction = GetActorLocation() - CurrentTarget->GetActorLocation();
		FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		Rotation.Yaw += 90.0f;
		SetActorRotation(Rotation);
	}
}

