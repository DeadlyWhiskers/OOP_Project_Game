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

	DummyRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(DummyRoot);
	//SetRootComponent(Collider);

	//Attaching objects to each other
	//Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//SpringArm->SetupAttachment(Collider);
	Sprite->SetupAttachment(DummyRoot);
	Collider->SetupAttachment(DummyRoot);
	Camera->SetupAttachment(DummyRoot);
	ShootFlash->SetupAttachment(Sprite, "Flash");

	//Setting starting sprite
	Sprite->Stop();
	Sprite->SetFlipbook(MoveDown);
	Sprite->SetPlaybackPositionInFrames(2, false);

	//Creating sharp movement
	Movement->Acceleration = 50000;
	Movement->Deceleration = 50000;
	
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
	ObjTraceChannel.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
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
}


//Spawning bullet
void ACC_PlayerClass::Shoot(const FInputActionValue& Value)
{
	//!!!Transfer this function to weapon class!!!
	FVector MuzzleLocation = Sprite->GetSocketLocation("Flash");
	MuzzleLocation.Z = this->GetActorLocation().Z;

	//Getting location in world where to shoot
	PC->GetHitResultUnderCursorForObjects(ObjTraceChannel, true, HitResult);
	MouseLocation.X = HitResult.Location.X;
	MouseLocation.Y = HitResult.Location.Y;

	//Sprite animating
	ShootFlash->PlayFromStart();

	const bool ShootValue = Value.Get<bool>();
	if (ShootValue) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "PEW");
	FActorSpawnParameters SP;
	SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FRotator ShootingDirection = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, MouseLocation);

	//Scattering
	ShootingDirection.Yaw += -Scatter + rand() % Scatter*2+1;
	//FTransform SpawnTransform;
	//SpawnTransform.SetRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MouseLocation));
	//SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * 100);
	GetWorld()->SpawnActor<AActor>(Ammo, Sprite->GetSocketLocation("Flash") + UKismetMathLibrary::GetForwardVector(ShootingDirection) * 1, ShootingDirection, SP);
	//Recoil test
	AddMovementInput(UKismetMathLibrary::GetForwardVector(ShootingDirection)*-1, GetWorld()->GetDeltaSeconds() * Recoil);
	
	//How to call a function from object
	//ABulletDef* BulletActor = Cast<ABulletDef>(GetWorld()->SpawnActor<AActor>(Ammo, SpawnTransform, SP));
	//BulletActor->SomeStupidFunction();

	//Camera recoil
	if ((Camera->GetComponentLocation() - CameraLocation).Length() <= 15)
	{
		Camera->AddWorldOffset(UKismetMathLibrary::GetForwardVector(ShootingDirection) * -1 * Recoil/2.25);
	}
}

//Moving player
void ACC_PlayerClass::Move(const FInputActionValue& Value)
{
	const FVector MovementDir = Value.Get<FVector>();

	Sprite->Play();

	AddMovementInput(GetActorRotation().RotateVector(MovementDir), GetWorld()->GetDeltaSeconds() * MoveSpeed);
	if (MovementDir.X > 0)
	{
		Sprite->SetFlipbook(MoveUp);
		return;
	}
	if (MovementDir.X < 0)
	{
		Sprite->SetFlipbook(MoveDown);
		return;
	}
	if (MovementDir.Y < 0)
	{
		Sprite->SetFlipbook(MoveLeft);
		return;
	}
	if (MovementDir.Y > 0)
	{
		Sprite->SetFlipbook(MoveRight);
		return;
	}
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
	
}

// Called to bind functionality to input
void ACC_PlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* NewInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	NewInput->BindAction(ShootAction, ETriggerEvent::Started, this, &ACC_PlayerClass::Shoot);
	NewInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::Move);
	NewInput->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ACC_PlayerClass::Rotate);
	NewInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACC_PlayerClass::UnsetSprite);

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

