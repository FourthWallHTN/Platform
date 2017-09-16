// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActor.h"
#include "Worker.h"
#include "CoreUObject.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Worker::JoyInit(PrimeNumbers, 50000, this);
	Super::BeginPlay();
}

void ATestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Worker::Shutdown();
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
