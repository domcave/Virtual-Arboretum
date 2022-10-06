// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"

// Sets default values
ANinja::ANinja()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANinja::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANinja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANinja::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

