// Fill out your copyright notice in the Description page of Project Settings.

#include "CC_PickableItem.h"

// Sets default values
ACC_PickableItem::ACC_PickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	SetRootComponent(Collider);
	SpriteComponent->SetupAttachment(Collider);
	SpriteComponent->SetSprite(Sprite);
}

// Called when the game starts or when spawned
void ACC_PickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACC_PickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACC_PickableItem::getId()
{
	return ItemId;
}

int ACC_PickableItem::getAmount()
{
	return Amount;
}

void ACC_PickableItem::setId(int newId)
{
	ItemId = newId;
	switch (ItemId)
	{
	case(0):
		SpriteComponent->SetSprite(MedicalKit);
		break;
	case(1):
		SpriteComponent->SetSprite(Ammo);
		break;
	case(2):
		SpriteComponent->SetSprite(Heart);
		break;
	default:
		break;
	}
}

void ACC_PickableItem::setAmount(int newAmount)
{
	Amount = newAmount;
}

void ACC_PickableItem::DestroyItem()
{
	Destroy();
}

