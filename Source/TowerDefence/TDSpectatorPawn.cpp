// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSpectatorPawn.h"

ATDSpectatorPawn::ATDSpectatorPawn() {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	MaxY = 2300.0f;
	MinY = 100.0f;

	MinX = -4400;
	MaxX = 100.0f;

	MovementSpeed = 1000;
}

void ATDSpectatorPawn::BeginPlay() {
	Super::BeginPlay();

	SetActorLocation(FVector(-2000.0f, 1500.0f, 1500.0f));
	SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));	
}

void ATDSpectatorPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!MovementInput.IsZero()) {
		MovementInput = MovementInput.GetSafeNormal() * MovementSpeed;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.Y * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.X * DeltaTime;
		SetActorLocation(NewLocation);
		MovementInput = FVector(0.0f, 0.0f, 0.0f);
	}
}

void ATDSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDSpectatorPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDSpectatorPawn::MoveRight);

	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &ATDSpectatorPawn::OnClickEscape);
	
}

void ATDSpectatorPawn::MoveForward(float AxisValue) {
	if (AxisValue > 0 && GetActorLocation().Y > MinY) {
		MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
	if (AxisValue < 0 && GetActorLocation().Y < MaxY) {
		MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}

void ATDSpectatorPawn::MoveRight(float AxisValue) {
	if (AxisValue < 0 && GetActorLocation().X > MinX) {
		MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
	if (AxisValue > 0 && GetActorLocation().X < MaxX) {
		MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}

void ATDSpectatorPawn::OnClickEscape() {

}