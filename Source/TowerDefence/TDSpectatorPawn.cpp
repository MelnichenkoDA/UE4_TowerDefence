// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSpectatorPawn.h"

ATDSpectatorPawn::ATDSpectatorPawn() {
	PrimaryActorTick.bCanEverTick = true;	

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera) {
		SetRootComponent(Camera);	
		Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}	

	BoxComponentCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	if (BoxComponentCollision) {
		BoxComponentCollision->AttachTo(RootComponent);
		BoxComponentCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		BoxComponentCollision->OnComponentBeginOverlap.AddDynamic(this, &ATDSpectatorPawn::BeginOverlap);
		BoxComponentCollision->OnComponentEndOverlap.AddDynamic(this, &ATDSpectatorPawn::EndOverlap);
	}

	MovementSpeed = 1000;
	
	bCanMoveRight = true;
	bCanMoveLeft = true;

	bCanMoveForward = true;
	bCanMoveBackward = true;
}

void ATDSpectatorPawn::BeginPlay() {
	Super::BeginPlay();

	SetActorRotation(FRotator(-45.0f, -90.0f, 0.0f));	
	SetActorLocation(FVector(-500.0, 1000.0f, 800.0f));
}

void ATDSpectatorPawn::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){	

	if (MovementInput.X > 0) {
		bCanMoveRight = false;
		BlockedDirections.Add(OtherActor->GetName(), &bCanMoveRight );
	} else if (MovementInput.X < 0) {
		bCanMoveLeft = false;
		BlockedDirections.Add(OtherActor->GetName(), &bCanMoveLeft);
	}

	if (MovementInput.Y > 0) {
		bCanMoveForward = false;
		BlockedDirections.Add(OtherActor->GetName(), &bCanMoveForward );
	}
	else if (MovementInput.Y < 0) {
		bCanMoveBackward = false;
		BlockedDirections.Add(OtherActor->GetName(), &bCanMoveBackward );
	}
}

void ATDSpectatorPawn::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){		
	if (BlockedDirections.Find(OtherActor->GetName())) {
		BlockedDirections.Remove(OtherActor->GetName());
		if (BlockedDirections.Num() == 0) {
			bCanMoveForward = bCanMoveBackward = bCanMoveLeft = bCanMoveRight = true;
		}
	}	
}

void ATDSpectatorPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!MovementInput.IsZero()) {
		MovementInput = MovementInput.GetSafeNormal() * MovementSpeed;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.Y * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.X * DeltaTime;
		NewLocation.Z = GetActorLocation().Z;
		SetActorLocation(NewLocation);
		MovementInput = FVector(0.0f, 0.0f, 0.0f);
	}
}

void ATDSpectatorPawn::MoveForward(float AxisValue) {
	if (AxisValue > 0 && bCanMoveForward) {
		MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
	if (AxisValue < 0 && bCanMoveBackward) {
		MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}

void ATDSpectatorPawn::MoveRight(float AxisValue) {
	if (AxisValue > 0 && bCanMoveRight) {
		MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
	if (AxisValue < 0 && bCanMoveLeft) {
		MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}
