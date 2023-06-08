// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Thing.h"
#include "CC_BulletParent.h"
#include "CC_PickableItem.h"

// Sets default values
ACC_Thing::ACC_Thing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Sprite = CreateAbstractDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_Thing::OnOverlapEnemy);
	SetRootComponent(Collider);
	Sprite->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ACC_Thing::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACC_Thing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACC_Thing::Death() {
	if (!pomerCpp)
	{
		pomerCpp = true;
		int randLoot = rand() % 101;
		if (randLoot > 75) {
			if (randLoot < 101) loot = 2;
			if (randLoot < 91) loot = 1;
			if (randLoot < 81) loot = 0;
			FActorSpawnParameters SP;
			SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ACC_PickableItem* Temp = Cast<ACC_PickableItem>(GetWorld()->SpawnActor<AActor>(Drop, this->GetActorLocation(), GetActorRotation(), SP));
			Temp->setId(loot);
			if (loot == 1) Temp->setAmount(30);
			else Temp->setAmount(1);
		}
		Sprite->SetFlipbook(Dead);
		OnDeath();
	}
}

void ACC_Thing::OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ACC_BulletParent* Temp = Cast<ACC_BulletParent>(OtherActor);
	if (Temp && !Temp->isEnemy())
	{
		UpdateHP();
		health = health - Temp->getDamage();
		//FRotator KickbackDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OtherActor->GetActorLocation());
		//AddMovementInput(UKismetMathLibrary::GetForwardVector(KickbackDirection) * -1, 2000);
	}
	if (health <= 0) {
		Death();
	}
	/*FActorSpawnParameters SP;
	SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	GetWorld()->SpawnActor<AActor>(Ammo, GetActorLocation() + UKismetMathLibrary::GetForwardVector(ShootingDirection) * 1, ShootingDirection, SP);*/
}