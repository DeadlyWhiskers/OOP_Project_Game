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

	UPROPERTY(EditAnywhere)
		int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Lifespan;
	UPROPERTY(EditAnywhere)
		bool Enemy;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int getDamage();
	bool isEnemy();
};