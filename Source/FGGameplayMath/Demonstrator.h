// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demonstrator.generated.h"

UCLASS(hidecategories=(Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class FGGAMEPLAYMATH_API ADemonstrator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemonstrator();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;
};