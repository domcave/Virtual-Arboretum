// Fill out your copyright notice in the Description page of Project Settings.


#include "Seeds.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASeeds::ASeeds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SeedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seed Mesh"));
	SeedMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASeeds::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASeeds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

