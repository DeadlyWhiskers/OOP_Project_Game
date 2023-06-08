// Fill out your copyright notice in the Description page of Project Settings.


#include "Thing.h"
#include "CC_BulletParent.h"
#include "CC_PickableItem.h"

// Sets default values
AThing::AThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Sprite = CreateAbstractDefaultSubobject<UPaperFlipbookComponent>("Sprite");

	SetRootComponent(Collider);
	Sprite->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void AThing::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThing::Death() {
	int randLoot = rand() % 101;
	if (randLoot > 75) {
		if (randLoot < 101) loot = 2;
		if (randLoot < 91) loot = 1;
		if (randLoot < 81) loot = 0;
		FRotator rotator;
		rotator.Roll = 0;
		rotator.Yaw = 0;
		rotator.Pitch = 0;
		FActorSpawnParameters SP;
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ACC_PickableItem* Temp = Cast<ACC_PickableItem>(GetWorld()->SpawnActor<AActor>(Drop, this->GetActorLocation(), rotator, SP));
		Temp->setId(loot);
		if (loot == 1) {
			Temp->setAmount(30);
		}
	}
	Sprite->SetFlipbook(Dead);
}

void AThing::OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ACC_BulletParent* Temp = Cast<ACC_BulletParent>(OtherActor);
	if (Temp)
	{
		health = health - Temp->getDamage();
		if (!health) Destroy();
	}
	if (health <= 0) {
		Death();
	}
	/*FActorSpawnParameters SP;
	SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	GetWorld()->SpawnActor<AActor>(Ammo, GetActorLocation() + UKismetMathLibrary::GetForwardVector(ShootingDirection) * 1, ShootingDirection, SP);*/
}