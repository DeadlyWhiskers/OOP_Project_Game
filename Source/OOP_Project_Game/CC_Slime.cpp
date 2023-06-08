// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Slime.h"

void ACC_Slime::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_Thing::OnOverlapEnemy);
}

ACC_Slime::ACC_Slime() {
	health = 20;
	Movement->MaxSpeed = 100;
	Movement->Acceleration = 50000;
	Movement->Deceleration = 50000;
	AttackSpeed = 150;
	speed = 0;
	pomerCpp = false;
}

void ACC_Slime::Attack()
{
	speed = AttackSpeed;
	Movement->MaxSpeed = 400;
}


void ACC_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (speed > 0) speed--;
	if (speed < (AttackSpeed / 4)*3 && !pomerCpp) Movement->MaxSpeed = 100;
	if (speed <= 0)
	{
		if (FVector::Distance(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation())<100 && !pomerCpp) Attack();
	}
}
