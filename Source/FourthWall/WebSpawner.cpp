// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSpawner.h"
#include "CoreUObject.h"
#include "Engine.h"
#include "WebviewActor.h"
#include "Core.h"


// Sets default values
AWebSpawner::AWebSpawner(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'Content/VirtualRealityBP/Blueprints/webview'"));
	if (ItemBlueprint.Object) {
		MyItemBlueprint = (UClass*)(ItemBlueprint.Object->GeneratedClass);
	}
}

// Called when the game starts or when spawned
void AWebSpawner::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	UWorld* const World = GetWorld();
	FActorSpawnParameters SpawnParams;
	const FVector Location(0.0f, 0.0f, 0.0f);
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	AWebviewActor * a = GetWorld()->SpawnActor<AWebviewActor>(Location, Rotation, SpawnParams);
	Super::BeginPlay();
}

// Called every frame
void AWebSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

