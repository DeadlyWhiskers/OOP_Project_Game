// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CC_BulletParent.generated.h"

UCLASS()
class OOP_PROJECT_GAME_API ACC_BulletParent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACC_BulletParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};