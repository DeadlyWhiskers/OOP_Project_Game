// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Fish.generated.h"

/**
 * 
 */
UCLASS()
class OOP_PROJECT_GAME_API AFish : public AEnemy
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* FlashFlipbook;
};
