// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CC_BulletParent.generated.h"

UCLASS()
class OOP_PROJECT_GAME_API ACC_BulletParent : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACC_BulletParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
