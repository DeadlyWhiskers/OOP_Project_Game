// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CC_Enemy.h"
#include "CC_Ghost.generated.h"

/**
 * 
 */
UCLASS()
class OOP_PROJECT_GAME_API ACC_Ghost : public ACC_Enemy
{
	GENERATED_BODY()
		void Attack() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ACC_Ghost();
	UPROPERTY(EditAnywhere, Category = Ammo)
		TSubclassOf<AActor> Ammo;
	FActorSpawnParameters SP;
};
