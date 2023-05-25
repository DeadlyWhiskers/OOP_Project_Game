// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Weapon.h"
#include "CC_PlayerClass.h"

CC_Weapon::CC_Weapon()
{
}

CC_Weapon::CC_Weapon(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType)
{
	WeaponOwner = thisWeaponOwner;
	Ammo = AmmoType;
	Camera = WeaponOwner->getCamera();
	Sprite = WeaponOwner->getSprite();
	ShootFlash = WeaponOwner->getShootFlash();
	CameraLocation = WeaponOwner->getCameraLocation();
	MinScatter = 0;
}

CC_Weapon::~CC_Weapon()
{
}

void CC_Weapon::Shoot(FVector MouseLocation)
{
	if (ShotDone == 0 && ReloadProgress == 0)
	{
		if (!isAutomatic) ShotDone = 1;
		ReloadProgress = ReloadTime;
		FVector MuzzleLocation = Sprite->GetSocketLocation("Flash");
		MuzzleLocation.Z = WeaponOwner->GetActorLocation().Z;
		if (Scatter < MaxScatter) Scatter += ScatterForce;

		//Sprite animating
		ShootFlash->PlayFromStart();
		FActorSpawnParameters SP;
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, MouseLocation);

		//Scattering
		if (Scatter != 0) ShootingDirection.Yaw += -Scatter + (rand() % ((int)Scatter * 2 + 1));
		//FTransform SpawnTransform;
		//SpawnTransform.SetRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MouseLocation));
		//SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * 100);
		WeaponOwner->GetWorld()->SpawnActor<AActor>(Ammo, Sprite->GetSocketLocation("Flash") + UKismetMathLibrary::GetForwardVector(ShootingDirection) * 1, ShootingDirection, SP);
		//Recoil test
		WeaponOwner->AddMovementInput(UKismetMathLibrary::GetForwardVector(ShootingDirection) * -1, WeaponOwner->GetWorld()->GetDeltaSeconds() * Recoil);

		//How to call a function from object
		//ABulletDef* BulletActor = Cast<ABulletDef>(GetWorld()->SpawnActor<AActor>(Ammo, SpawnTransform, SP));
		//BulletActor->SomeStupidFunction();

		//Camera recoil
		if ((Camera->GetComponentLocation() - *CameraLocation).Length() <= 15)
		{
			Camera->AddWorldOffset(UKismetMathLibrary::GetForwardVector(ShootingDirection) * -1 * Recoil / 2.25);
		}
	}
}

void CC_Shotgun::Shoot(FVector MouseLocation)
{
	if (ShotDone == 0 && ReloadProgress == 0)
	{
		if (!isAutomatic) ShotDone = 1;
		ReloadProgress = ReloadTime;
		FVector MuzzleLocation = Sprite->GetSocketLocation("Flash");
		MuzzleLocation.Z = WeaponOwner->GetActorLocation().Z;
		Scatter = MinScatter;

		//Sprite animating
		ShootFlash->PlayFromStart();
		FActorSpawnParameters SP;
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, MouseLocation);

		//Scattering
		for(int i = 0; i<NumOfBullets; i++)
		{
			Scatter += ScatterForce;
			if (Scatter != 0) ShootingDirection.Yaw += -Scatter + (rand() % ((int)Scatter * 2 + 1));
			WeaponOwner->GetWorld()->SpawnActor<AActor>(Ammo, Sprite->GetSocketLocation("Flash") + UKismetMathLibrary::GetForwardVector(ShootingDirection) * ((double)rand()/RAND_MAX)*8, ShootingDirection, SP);
			WeaponOwner->AddMovementInput(UKismetMathLibrary::GetForwardVector(ShootingDirection) * -1, WeaponOwner->GetWorld()->GetDeltaSeconds() * Recoil);
		}
		//How to call a function from object
		//ABulletDef* BulletActor = Cast<ABulletDef>(GetWorld()->SpawnActor<AActor>(Ammo, SpawnTransform, SP));
		//BulletActor->SomeStupidFunction();

		//Camera recoil
		if ((Camera->GetComponentLocation() - *CameraLocation).Length() <= 15)
		{
			Camera->AddWorldOffset(UKismetMathLibrary::GetForwardVector(ShootingDirection) * -1 * Recoil / 2.25);
		}
	}
}


void CC_Weapon::CoolDown()
{
	if (Scatter > MinScatter) Scatter -= 0.1;
	else if (Scatter < MinScatter) Scatter = MinScatter;
}

void CC_Weapon::ShootEnd()
{
	ShotDone = 0;
}

void CC_Weapon::Reload()
{
	if (ReloadProgress > 0)
	{
		ReloadProgress--;
	}
}

int CC_Weapon::getWeaponID()
{
	return WeaponId;
}

int CC_Weapon::getReloadProgress()
{
	return ReloadProgress;
}

CC_Pistol::CC_Pistol(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType) : CC_Weapon(thisWeaponOwner, AmmoType)
{
	WeaponId = 1;
	MaxScatter = 7.5;
	ScatterForce = 2.5;
	Scatter = 0;
	Recoil = 8;
	ReloadTime = 15;
	ReloadProgress = 0;
	isAutomatic = 0;
	ShotDone = 0;
}

CC_Pistol::~CC_Pistol()
{
}

CC_AssaultRifle::CC_AssaultRifle(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType) : CC_Weapon(thisWeaponOwner, AmmoType)
{
	WeaponId = 2;
	MaxScatter = 7.5;
	ScatterForce = 1.5;
	Scatter = 0;
	Recoil = 6;
	ReloadTime = 5;
	ReloadProgress = 0;
	isAutomatic = 1;
	ShotDone = 0;
}

CC_Shotgun::CC_Shotgun(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType) : CC_Weapon(thisWeaponOwner, AmmoType)
{
	WeaponId = 3;
	MinScatter = 2;
	MaxScatter = 20;
	NumOfBullets = 5;
	ScatterForce = (MaxScatter-MinScatter)/NumOfBullets;
	Scatter = 0;
	Recoil = 15;
	ReloadTime = 40;
	ReloadProgress = 0;
	isAutomatic = 0;
	ShotDone = 0;
}

CC_AssaultRifle::~CC_AssaultRifle()
{
}

CC_Shotgun::~CC_Shotgun()
{
}
