// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Ghost.h"

void ACC_Ghost::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_Thing::OnOverlapEnemy);
	SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
}

ACC_Ghost::ACC_Ghost() {
	health = 15;
	Movement->MaxSpeed = 50;
	Movement->Acceleration = 50000;
	Movement->Deceleration = 50000;
	AttackSpeed = 90;
	speed = 0;
	pomerCpp = false;
}

void ACC_Ghost::Attack()
{
	speed = AttackSpeed;
	FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	GetWorld()->SpawnActor<AActor>(Ammo, GetActorLocation() + UKismetMathLibrary::GetForwardVector(ShootingDirection) * 5, ShootingDirection, SP);
}


void ACC_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (speed > 0) speed--;
		if (speed <= 0)
		{
			if(!pomerCpp) Attack();
		}
}