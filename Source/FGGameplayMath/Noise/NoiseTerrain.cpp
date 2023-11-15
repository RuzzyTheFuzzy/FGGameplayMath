// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseTerrain.h"
#include "KismetProceduralMeshLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ANoiseTerrain::ANoiseTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProceduralMeshComponent->SetupAttachment(GetRootComponent());
}

void ANoiseTerrain::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GenerateNoiseMap();
	GenerateMesh();

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV, Normals, Tangents);

	ProceduralMeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UV, Colors, Tangents, true);
	ProceduralMeshComponent->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void ANoiseTerrain::BeginPlay()
{
	Super::BeginPlay();

	GenerateNoiseMap();
	GenerateMesh();

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV, Normals, Tangents);

	ProceduralMeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UV, Colors, Tangents, true);
	ProceduralMeshComponent->SetMaterial(0, Material);
}

void ANoiseTerrain::GenerateNoiseMap()
{
	NoiseArray.SetNum((Resolution + 1) * (Resolution + 1));

	for (auto Y = 0; Y <= Resolution; Y++)
	{
		for (auto X = 0; X <= Resolution; X++)
		{
			const FVector2D Position = FVector2D(
				((static_cast<float>(X) + Offset.X) + .1f) * Scale,
				((static_cast<float>(Y) + Offset.Y) + .1f) * Scale);
			
			const int32 Index = Y * Resolution + X;
			NoiseArray[Index] = FMath::PerlinNoise2D(Position) * Strength;
		}
	}
}

void ANoiseTerrain::GenerateMesh()
{
	Vertices.SetNum((Resolution + 1) * (Resolution + 1));
	Triangles.SetNum(Resolution * Resolution * 6);
	Colors.SetNum(Vertices.Num());
	Normals.SetNum(Vertices.Num());
	UV.SetNum(Vertices.Num());

	const float StepSize = 1.f / Resolution;

	for (int v = 0, y = 0; y <= Resolution; y++)
	{
		for (int x = 0; x <= Resolution; x++, v++)
		{
			const int32 Index = y * Resolution + x;
			const float Noise = NoiseArray[Index];
			Vertices[v] = FVector((x * StepSize - .5f), (y * StepSize - .5f), Noise) * ProcMeshScale;
			UV[v] = FVector2D(x * StepSize, y * StepSize);
		}
	}

	for (int t = 0, v = 0, y = 0; y < Resolution; y++, v++)
	{
		for (int x = 0; x < Resolution; x++, v++, t += 6)
		{
			Triangles[t] = v;
			Triangles[t + 1] = v + Resolution + 1;
			Triangles[t + 2] = v + 1;

			Triangles[t + 3] = v + Resolution + 1;
			Triangles[t + 4] = v + Resolution + 2;
			Triangles[t + 5] = v + 1;
		}
	}

	CalculateNormals();
}

void ANoiseTerrain::CalculateNormals()
{
	for (int v = 0, y = 0; y <= Resolution; y++)
	{
		for (int x = 0; x <= Resolution; x++, v++)
		{
			FVector Normal = FVector::UpVector;
			Normal.Z = FMath::Square(1.f - (Normal.X * Normal.X + Normal.Y * Normal.Y));
			Normals[v] = Normal;
		}
	}
}

// Called every frame
void ANoiseTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Offset.X += 0.01;
	Offset.Y += 0.01;

	GenerateNoiseMap();
	GenerateMesh();

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV, Normals, Tangents);

	ProceduralMeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UV, Colors, Tangents, true);
	ProceduralMeshComponent->SetMaterial(0, Material);
	
	//return;

	// This debugging gets very expensive at high resolutions - avoid
	// for (int i = 0; i < Vertices.Num(); i++)
	// {
	// 	/*
	// 	FString DebugString;
	// 	DebugString.Append(FString::SanitizeFloat(NoiseArray[i]));
	// 	DebugString.Append(":");
	// 	DebugString.Append(FString::FromInt(i));
	// 	*/
	//
	// 	DrawDebugPoint(GetWorld(), Vertices[i], 5.f, FColor::Red);
	// 	//DrawDebugString(GetWorld(), Vertices[i], DebugString);
	// }
}