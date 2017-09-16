// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebSpawner.generated.h"

UCLASS()
class FOURTHWALL_API AWebSpawner : public AActor
{
	GENERATED_BODY()
	TSubclassOf<class AActor> MyItemBlueprint;

public:
	// Sets default values for this pawn's properties
	AWebSpawner(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
