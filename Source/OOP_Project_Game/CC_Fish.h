
#pragma once

#include "CoreMinimal.h"
#include "CC_Enemy.h"
#include "CC_Fish.generated.h"

/**
 *
 */
UCLASS()
class OOP_PROJECT_GAME_API ACC_Fish : public ACC_Enemy
{
    GENERATED_BODY()

    virtual void BeginPlay() override;
protected:
    ACC_Fish();
};