// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CC_Thing.h"
#include "CC_Enemy.generated.h"

/**
 *
 */
UCLASS()
class OOP_PROJECT_GAME_API ACC_Enemy : public ACC_Thing
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
        class UFloatingPawnMovement* Movement;
    UPROPERTY(EditAnywhere, Category = Input)
        float MoveSpeed;
    int damage, AttackSpeed, speed;
    bool isDead;
    
public:
    ACC_Enemy();
    virtual void Attack();
};