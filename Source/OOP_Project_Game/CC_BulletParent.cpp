// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_BulletParent.h"

// Sets default values
ACC_BulletParent::ACC_BulletParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACC_BulletParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACC_BulletParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

