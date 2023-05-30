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
#include <deque>
#include "CC_Weapon.h"

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
	FVector CameraLocation;
	int MovingDirection;
	bool isDead;

	CC_Weapon * AssaultRifle, * Pistol, *Shotgun;
	std::deque<CC_Weapon*> Weapons;
	std::deque<CC_Weapon*>::iterator CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = Ammo)
		TSubclassOf<AActor> PistolAmmo;
	UPROPERTY(EditAnywhere, Category = Ammo)
		TSubclassOf<AActor> AssaultAmmo;
	UPROPERTY(EditAnywhere, Category = Ammo)
		TSubclassOf<AActor> ShotgunAmmo;
	//UPROPERTY(EditAnywhere, Category = Enemy)
		//TArray<TEnumAsByte<EObjectTypeQuery>> ObjTraceChannel;

	//Structure.....................................
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collider;
	/*
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* Sprite;
	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* ShootFlash;
	//End of structure.....................................
	
	//Input.....................................
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputMappingContext* MapContext;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* SwitchWeaponAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* RotateAction;
	UPROPERTY(EditAnywhere, Category = Input)
		class UFloatingPawnMovement* Movement;
	//End of input.....................................

	UPROPERTY(EditAnywhere, Category = Input)
		float MoveSpeed;
	UPROPERTY(EditAnywhere, Category = Input)
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//Temp test
		FVector MousePos;

	//Sprites.....................................
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* FlashFlipbook;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* DefaultPose;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveUp;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveDown;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveLeft;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveRight;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* Death;


	//Pistol.............................
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveUpPistol;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveDownPistol;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveLeftPistol;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveRightPistol;
	//AssaultRifle...........................
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveUpAssaultRifle;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveDownAssaultRifle;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveLeftAssaultRifle;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveRightAssaultRifle;
	//Shotgun...................................
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveUpShotgun;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveDownShotgun;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveLeftShotgun;
	UPROPERTY(EditAnywhere, Category = "Sprites")
		UPaperFlipbook* MoveRightShotgun;
	//End Of sprites.....................................

	//Overlaps.....................................
	UFUNCTION()
		void OnHitEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//FHitResult HitResult;
	FVector HitResult, HitResultDir;
	//End of overlaps.....................................

	//ActionFunctions.....................................
	void Shoot(const FInputActionValue& Value);
	void ShootEnd(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void SwitchWeapon(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void SwitchPlayerModel(int NewWeapon);
	void Die();

	//End of action functions.....................................

	void UnsetSprite(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPaperFlipbookComponent* getSprite();
	UPaperFlipbookComponent* getShootFlash();
	UCameraComponent* getCamera();
	FVector* getCameraLocation();

	UFUNCTION(BlueprintImplementableEvent)
		void OnWeaponSwitch();

	UFUNCTION(BlueprintImplementableEvent)
		void OnShoot();

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHP();

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateReloadProgress();

	UFUNCTION(BlueprintImplementableEvent)
		void OnDeath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MouseLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentWeaponReload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentWeaponReloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentWeaponId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentBullets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxHealth;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
