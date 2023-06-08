// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Thing.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class OOP_PROJECT_GAME_API AEnemy : public AThing
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Input)
		class UFloatingPawnMovement* Movement;
	int damage, AttackSpeed, speed;
	bool isDead;
	UFUNCTION(BlueprintImplementableEvent)
		void OnDeath();
public:
	AEnemy();
	virtual void Attack() = 0;
	//int Damage();
	
};
