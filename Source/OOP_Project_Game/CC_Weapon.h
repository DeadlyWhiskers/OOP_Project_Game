// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ACC_PlayerClass;
class UPaperFlipbookComponent;
class UCameraComponent;

/**
 * 
 */
class OOP_PROJECT_GAME_API CC_Weapon
{
protected:
	double MaxScatter, MinScatter, ScatterForce, Scatter;
	int Recoil, ReloadTime, ReloadProgress, WeaponId, Bullets;
	bool isAutomatic, ShotDone;
	TSubclassOf<AActor> Ammo;
	ACC_PlayerClass* WeaponOwner;
	UPaperFlipbookComponent* Sprite,* ShootFlash;
	UCameraComponent* Camera;
	FVector* CameraLocation;

public:
	CC_Weapon();
	CC_Weapon(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType);
	virtual void Shoot(FVector MouseLocation);
	void CoolDown();
	void Reload();
	void ShootEnd();
	virtual void AddBullets(int AdditionalBullets);
	virtual ~CC_Weapon();
	int getWeaponID();
	int getReloadProgress();
	int getReloadTime();
	int GetBullets();
};

class CC_Pistol : public CC_Weapon
{
public:
	CC_Pistol(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType, int Bullets);
	~CC_Pistol();
};

class CC_AssaultRifle : public CC_Weapon
{
public:
	CC_AssaultRifle(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType, int Bullets);
	~CC_AssaultRifle();
	void AddBullets(int AdditionalBullets) override;
};

class CC_Shotgun : public CC_Weapon
{
protected:
	int NumOfBullets;
public:
	void Shoot(FVector MouseLocation) override;
	void AddBullets(int AdditionalBullets) override;
	CC_Shotgun(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType, int Bullets);
	~CC_Shotgun();
};