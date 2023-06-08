// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Thing.generated.h"

UCLASS()
class OOP_PROJECT_GAME_API AThing : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
//	virtual void Death();
	UPROPERTY(EditAnywhere, Category = Drop)
		TSubclassOf<AActor> Drop;
	/*UFUNCTION()
		void OnHitActor();*/
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* Sprite;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* Dead;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int loot;
	virtual void Death();
	void OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
