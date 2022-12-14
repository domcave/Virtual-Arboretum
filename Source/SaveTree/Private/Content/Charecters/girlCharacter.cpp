// Copyright Epic Games, Inc. All Rights Reserved.
#include "Content/Charecters/girlCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "..\..\..\Public\Content\Charecters\girlCharacter.h"


//////////////////////////////////////////////////////////////////////////
// ATest3Character

AgirlCharacter::AgirlCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned

void AgirlCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Seed = GetWorld()->SpawnActor<ASeeds>(SeedClass);
	
	//Seed->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket2"));
	//Seed->SetOwner(this);
}
void AgirlCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AgirlCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AgirlCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AgirlCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AgirlCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AgirlCharacter::Shoot);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AgirlCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AgirlCharacter::TouchStopped);
}

void AgirlCharacter::Shoot()
{
	//FVector LocationOfTip = GetActorLocation();



	//FVector ViewLocation = Camera->GetComponentLocation();// FVector(0, 0, 0);
	//FRotator ViewRotation = Camera->GetComponentRotation();// FRotator(0, 0, 0);


	//FVector End = (ViewLocation + ViewRotation.Vector() * shootRange);

	//FCollisionQueryParams Params;
	//Params.AddIgnoredActor(this);
	//Params.AddIgnoredActor(GetOwner());
	//ASeeds* SpawnedSeed = GetWorld()->SpawnActor<ASeeds>(Seed, GetMovementComponent()->GetActorTransform(), Params);
	//DrawDebugLine(GetWorld(), LocationOfTip, End, FColor::Red, false, 2.f, 0, 2.f);
}

void AgirlCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AgirlCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AgirlCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AgirlCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}



void AgirlCharacter::MoveForward(float Value)
{
	//AddMovementInput(GetActorRightVector() * Value);
	
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AgirlCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}












/*// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/Charecters/girlCharacter.h"

// Sets default values
AgirlCharacter::AgirlCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AgirlCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AgirlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AgirlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AgirlCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AgirlCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

}


void AgirlCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}


void AgirlCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
*/

