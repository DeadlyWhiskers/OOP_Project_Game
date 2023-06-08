// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Fish.h"

ACC_Fish::ACC_Fish() {
	health = 30;
	Movement->MaxSpeed = 150;
	Movement->Acceleration = 50000;
	Movement->Deceleration = 50000;
	pomerCpp = false;
}

void ACC_Fish::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_Thing::OnOverlapEnemy);
}