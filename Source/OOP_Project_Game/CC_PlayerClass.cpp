// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_PlayerClass.h"

//to create simmilar classes
//#include "BulletDef.h"
//#include "Moving/TargetParent.h"

// Sets default values
ACC_PlayerClass::ACC_PlayerClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHealth = 3;

	//Creating object structure
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	Sprite = CreateAbstractDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	ShootFlash = CreateAbstractDefaultSubobject<UPaperFlipbookComponent>("Flash");

	//DummyRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Collider);
	//SetRootComponent(Collider);

	//Attaching objects to each other
	//Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//SpringArm->SetupAttachment(Collider);
	Sprite->SetupAttachment(Collider);
	Collider->SetupAttachment(Collider);
	Camera->SetupAttachment(Collider);
	ShootFlash->SetupAttachment(Sprite, "Flash");

	//Setting starting sprite
	Sprite->Stop();
	Sprite->SetFlipbook(MoveDown);
	Sprite->SetPlaybackPositionInFrames(2, false);

	//Creating sharp movement
	Movement->Acceleration = 25000;
	Movement->Deceleration = 35000;
	
}

// Called when the game starts or when spawned
void ACC_PlayerClass::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	srand(time(NULL));
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	Subsystem->AddMappingContext(MapContext, 0);
	//ObjTraceChannel.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	Collider->OnComponentHit.AddDynamic(this, &ACC_PlayerClass::OnHitEnemy);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_PlayerClass::OnOverlapEnemy);
	MouseLocation.Z = GetActorLocation().Z;

	//Flash animation
	ShootFlash->SetFlipbook(FlashFlipbook);
	ShootFlash->SetLooping(false);
	ShootFlash->SetPlaybackPositionInFrames(5, false);

	//Temporary
	CameraLocation.Set(this->GetActorLocation().X, this->GetActorLocation().Y, 150);
	Camera->SetWorldLocation(CameraLocation);

	//Weapon setting up
	Pistol = new CC_Pistol(this, PistolAmmo);
	AssaultRifle = new CC_AssaultRifle(this, AssaultAmmo);
	Shotgun = new CC_Shotgun(this, ShotgunAmmo);
	Weapons.push_back(Pistol);
	Weapons.push_back(AssaultRifle);
	Weapons.push_back(Shotgun);
	CurrentWeapon = Weapons.begin();
	CurrentWeaponId = (*CurrentWeapon)->getWeaponID();
	CurrentWeaponReloadTime = (*CurrentWeapon)->getReloadTime();
	UpdateHP();
	OnWeaponSwitch();
	SwitchPlayerModel(CurrentWeaponId);
	MovingDirection = 0;
	PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
}


//Spawning bullet
void ACC_PlayerClass::Shoot(const FInputActionValue& Value)
{
	//PC->GetHitResultUnderCursorForObjects(ObjTraceChannel, true, HitResult);
	//PC->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	PC->DeprojectMousePositionToWorld(HitResult, HitResultDir);
	/*MouseLocation.X = HitResult.Location.X;
	MouseLocation.Y = HitResult.Location.Y;*/
	MouseLocation.X = HitResult.X;
	MouseLocation.Y = HitResult.Y;
	OnShoot();
	(*CurrentWeapon)->Shoot(MouseLocation);
}

void ACC_PlayerClass::ShootEnd(const FInputActionValue& Value)
{
	(*CurrentWeapon)->ShootEnd();
}

//Moving player
void ACC_PlayerClass::Move(const FInputActionValue& Value)
{
	const FVector MovementDir = Value.Get<FVector>();

	Sprite->Play();

	AddMovementInput(GetActorRotation().RotateVector(MovementDir), GetWorld()->GetDeltaSeconds() * MoveSpeed);
	if (MovementDir.X > 0)
	{
		MovingDirection = 0;
		Sprite->SetFlipbook(MoveUp);
		return;
	}
	if (MovementDir.X < 0)
	{
		MovingDirection = 1;
		Sprite->SetFlipbook(MoveDown);
		return;
	}
	if (MovementDir.Y < 0)
	{
		MovingDirection = 2;
		Sprite->SetFlipbook(MoveLeft);
		return;
	}
	if (MovementDir.Y > 0)
	{
		MovingDirection = 3;
		Sprite->SetFlipbook(MoveRight);
		return;
	}
}

void ACC_PlayerClass::SwitchWeapon(const FInputActionValue& Value)
{
	float SwitchDirection = Value.Get<float>();
	if (SwitchDirection>0)
	{
		CurrentWeapon++;
		if (CurrentWeapon == Weapons.end()) CurrentWeapon = Weapons.begin();
	}
	else
	{
		if (CurrentWeapon == Weapons.begin()) CurrentWeapon = Weapons.end() - 1;
		else CurrentWeapon--;
	}
	CurrentWeaponId = (*CurrentWeapon)->getWeaponID();
	SwitchPlayerModel(CurrentWeaponId);
	CurrentWeaponReloadTime = (*CurrentWeapon)->getReloadTime();
	OnWeaponSwitch();
}


//Rotationg player(probably unused)
void ACC_PlayerClass::Rotate(const FInputActionValue& Value)
{
	FRotator Rotation(0, Value.Get<float>(), 0);
	Rotation = GetActorRotation() + Rotation * GetWorld()->GetDeltaSeconds() * RotationSpeed;
	SetActorRotation(Rotation);
}

//Funtion to apply standing sprite
void ACC_PlayerClass::UnsetSprite(const FInputActionValue& Value)
{
	Sprite->Stop();
	Sprite->SetPlaybackPositionInFrames(2, false);
}

// Called every frame
void ACC_PlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Temporary camera movement system
	FVector DistanceVector = CameraLocation - this->GetActorLocation();
	DistanceVector.Z = 0;
	if (DistanceVector.Length() > 200)
	{
		CameraLocation = this->GetActorLocation();
		CameraLocation.Z = 150;
		Camera->SetWorldLocation(CameraLocation);
	}

	//Recoil movement restoration
	int CamRecoil = (Camera->GetComponentLocation() - CameraLocation).Length();
	if (CamRecoil > 0)
	{
		//UKismetMathLibrary::FindLookAtRotation(CameraLocation, Camera->GetComponentLocation());
		Camera->AddWorldOffset((CameraLocation - Camera->GetComponentLocation()).GetSafeNormal()*DeltaTime*15* (sqrt(CamRecoil)/3+1));
	}
	
	//Reload
	(*CurrentWeapon)->Reload();
	CurrentWeaponReload = (*CurrentWeapon)->getReloadProgress();
	UpdateReloadProgress();
	//Scatter decrease
	(*CurrentWeapon)->CoolDown();
}

UPaperFlipbookComponent* ACC_PlayerClass::getSprite()
{
	return Sprite;
}

UPaperFlipbookComponent* ACC_PlayerClass::getShootFlash()
{
	return ShootFlash;
}

UCameraComponent* ACC_PlayerClass::getCamera()
{
	return Camera;
}

FVector* ACC_PlayerClass::getCameraLocation()
{
	return &CameraLocation;
}

// Called to bind functionality to input
void ACC_PlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* NewInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	NewInput->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::Shoot);
	NewInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::Move);
	NewInput->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::Rotate);
	NewInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACC_PlayerClass::UnsetSprite);
	NewInput->BindAction(ShootAction, ETriggerEvent::Completed, this, &ACC_PlayerClass::ShootEnd);
	NewInput->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::SwitchWeapon);

}

void ACC_PlayerClass::SwitchPlayerModel(int NewWeapon)
{
	switch (NewWeapon)
	{
	case(1):
	{
		MoveUp = MoveUpPistol;
		MoveDown = MoveDownPistol;
		MoveLeft = MoveLeftPistol;
		MoveRight = MoveRightPistol;
		break;
	}
	case(2):
	{
		MoveUp = MoveUpAssaultRifle;
		MoveDown = MoveDownAssaultRifle;
		MoveLeft = MoveLeftAssaultRifle;
		MoveRight = MoveRightAssaultRifle;
		break;
	}
	case(3):
	{
		MoveUp = MoveUpShotgun;
		MoveDown = MoveDownShotgun;
		MoveLeft = MoveLeftShotgun;
		MoveRight = MoveRightShotgun;
		break;
	}
	default:
	{
		break;
	}
	}
	switch (MovingDirection)
	{
	case(0):
	{
		Sprite->SetFlipbook(MoveUp);
		break;
	}
	case(1):
	{
		Sprite->SetFlipbook(MoveDown);
		break;
	}
	case(2):
	{
		Sprite->SetFlipbook(MoveLeft);
		break;
	}
	case(3):
	{
		Sprite->SetFlipbook(MoveRight);
		break;
	}
	default: break;
	}
	Sprite->SetPlaybackPositionInFrames(2, false);
}

//Functions to set overlap and hit events(getting damange etc.)

void ACC_PlayerClass::OnHitEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//to add enemy class and apply here
	//ATargetParent* Temp = Cast<ATargetParent>(OtherActor);
	//if (Temp)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("%s"), *OtherActor->GetName()));
	//	/*health--;
	//	if (!health) Destroy();*/
	//}
}

void ACC_PlayerClass::OnOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//to add enemy class and apply here
	/*ATargetParent* Temp = Cast<ATargetParent>(OtherActor);
	if (Temp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("%s"), *OtherActor->GetClass()->GetName()));
		health--;
		if (!health) Destroy();
	}*/

	//Самый жёсткий в мире костыль, но такой рабочий и удобный))
	/*if (OtherActor->GetClass()->GetName() == "target_C")
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("%s"), *OtherActor->GetClass()->GetName()));
		Destroy();
	}*/
}

