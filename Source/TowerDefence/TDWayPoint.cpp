// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWayPoint.h"

// Sets default values
ATDWayPoint::ATDWayPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponentCollision = CreateDefaultSubobject<UBoxComponent>("RootComponent");
	if (BoxComponentCollision) {
		SetRootComponent(BoxComponentCollision);
		BoxComponentCollision->SetGenerateOverlapEvents(true);
	}

	NextPoint = nullptr;
}

// Called when the game starts or when spawned
void ATDWayPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATDWayPoint::SetNextPoint(ATDWayPoint* Point){
	NextPoint = Point;	
}

ATDWayPoint* ATDWayPoint::GetNextPoint(){
	return NextPoint;
}

