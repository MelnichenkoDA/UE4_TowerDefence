// Fill out your copyright notice in the Description page of Project Settings.


#include "TDDamageTypeFlame.h"

float UTDDamageTypeFlame::Timer = 5.0f;

UTDDamageTypeFlame::UTDDamageTypeFlame() {
	
}

void UTDDamageTypeFlame::InitDamage(float& Timer){
	Timer = this->Timer;
}
