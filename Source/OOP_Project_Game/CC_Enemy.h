
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CC_Enemy.h"
#include "CC_Enemy.generated.h"

/**
 *
 */
UCLASS()
class OOP_PROJECT_GAME_API ACC_Enemy : public ACC_Enemy
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, Category = Input)
        class UFloatingPawnMovement* Movement;
    UPROPERTY(EditAnywhere, Category = Input)
        float MoveSpeed;
    int damage, AttackSpeed, speed;
    bool isDead;
public:
    ACC_Enemy();
    virtual void Attack() = 0;
};