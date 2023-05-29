// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "CC_PickableItem.generated.h"

UCLASS()
class OOP_PROJECT_GAME_API ACC_PickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACC_PickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		int ItemId;
	UPROPERTY(EditAnywhere)
		int Amount;


	//id 0 - first aid, id 1 - ammo, id 2 - heart;
	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* SpriteComponent;
	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite * Sprite;
	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite * MedicalKit;
	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite * Ammo;
	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite *Heart;
	UPROPERTY(EditAnywhere, Category = "Sprites")
	UBoxComponent* Collider;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int getId();
	int getAmount();
	void setId(int newId);
	void setAmount(int newAmount);
	void DestroyItem();
};
