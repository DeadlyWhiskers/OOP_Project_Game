// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"

#include "CC_PlayerClass.generated.h"

UCLASS()
class OOP_PROJECT_GAME_API ACC_PlayerClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACC_PlayerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MouseLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxHealth;
	UPROPERTY(EditAnywhere, Category = Enemy)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjTraceChannel;

	//Structure.....................................
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collider;
	/*
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* Sprite;
	//End of structure.....................................

	//Input.....................................
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputMappingContext* MapContext;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* RotateAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UFloatingPawnMovement* Movement;
	//End of input.....................................

	UPROPERTY(EditAnywhere, Category = Input)
		float MoveSpeed;
	UPROPERTY(EditAnywhere, Category = Input)
		float RotationSpeed;
	UPROPERTY(EditAnywhere, Category = Ammo)
		TSubclassOf<AActor> Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//Temp test
		FVector MousePos;

	//Sprites.....................................
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* DefaultPose;
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* MoveUp;
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* MoveDown;
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* MoveLeft;
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* MoveRight;
	//End Of sprites.....................................

	//Overlaps.....................................
	UFUNCTION()
		void OnHitEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	FHitResult HitResult;
	//End of overlaps.....................................

	//ActionFunctions.....................................
	void Shoot(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	//End of action functions.....................................

	void UnsetSprite(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
