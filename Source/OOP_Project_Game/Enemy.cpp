// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "CC_BulletParent.h"

AEnemy::AEnemy() {
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapEnemy);
}


