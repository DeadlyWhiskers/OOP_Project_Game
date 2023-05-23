// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Weapon.h"

CC_Weapon::CC_Weapon()
{
}

CC_Weapon::CC_Weapon(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType)
{
}

CC_Weapon::~CC_Weapon()
{
}

void CC_Weapon::Shoot(FVector MousePosition)
{
}

CC_Pistol::CC_Pistol(ACC_PlayerClass* thisWeaponOwner, TSubclassOf<AActor> AmmoType) : CC_Weapon(thisWeaponOwner, AmmoType)
{
}

CC_Pistol::~CC_Pistol()
{
}
