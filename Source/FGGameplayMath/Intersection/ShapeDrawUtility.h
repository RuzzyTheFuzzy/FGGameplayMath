// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShapeDrawUtility.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UShapeDrawUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Box(
		const UWorld* WorldContext,
		const FVector Location,
		const FVector& Min,
		const FVector& Max,
		const FColor& Color)
	{
		const auto A = FVector(Min.X, Min.Y, Max.Z);
		const auto B = FVector(Max.X, Max.Y, Min.Z);
		const auto C = FVector(Min.X, Max.Y, Min.Z);
		const auto D = FVector(Max.X, Min.Y, Max.Z);
		const auto E = FVector(Max.X, Min.Y, Min.Z);
		const auto F = FVector(Min.X, Max.Y, Max.Z);
		
		DrawDebugPoint(
			WorldContext,
			Location + Min,
			25.f,
			Color
			);

		DrawDebugPoint(
			WorldContext,
			Location + Max,
			25.f,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + B,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + A,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + C,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + C,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + C,
			Location + B,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + D,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + D,
			Location + A,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + A,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + D,
			Location + E,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + B,
			Location + E,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + E,
			Color
			);	
	}

	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Sphere(
		const UWorld* WorldContext,	
		const FVector& Center,
		const float& Radius,
		const FColor& Color)
	{
		DrawDebugSphere(
			WorldContext,
			Center,
			Radius,
			16,
			Color
			);
	}

	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Ray(
		const UWorld* WorldContext,	
		const FVector& Origin,
		const FVector& Direction,
		const FColor& Color)
	{
		DrawDebugLine(
			WorldContext,
			Origin,
			Origin + (Direction * 1000.f),
			Color
			);		
	}	

	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Plane(
		const UWorld* WorldContext,	
		const FVector& Location,
		const FVector& Normal,
		const FQuat& Quat,
		const FColor& Color)
	{
		// The size of the drawn plane
		const auto PlaneExtents = FVector(
			1000.f,
			1000.f,
			0.f
			);	
		
		DrawDebugPoint(
			WorldContext,
			Location,
			25.f,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location,
			Location + (Normal * 100.f),
			Color
			);
		
		DrawDebugBox(
			WorldContext,
			Location,
			PlaneExtents,
			Quat,
			Color
			);
	}

	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Triangle(
		const UWorld* WorldContext,	
		const FTransform& Transform,
		const FVector& V0,
		const FVector& V1,
		const FVector& V2,
		const FColor& Color)
	{
		// Transformations for the triangle used in intersection
		const FVector TransformedV0 = Transform.TransformPosition(V0);
		const FVector TransformedV1 = Transform.TransformPosition(V1);
		const FVector TransformedV2 = Transform.TransformPosition(V2);
		
		DrawDebugPoint(
			WorldContext,
			TransformedV0,
			25.f,
			Color);

		DrawDebugPoint(
			WorldContext,
			TransformedV1,
			25.f,
			Color);

		DrawDebugPoint(
			WorldContext,
			TransformedV2,
			25.f,
			Color);		
		
		DrawDebugLine(
			WorldContext,
			TransformedV0,
			TransformedV1,
			Color
			);

		DrawDebugLine(
			WorldContext,
			TransformedV1,
			TransformedV2,
			Color
			);

		DrawDebugLine(
			WorldContext,
			TransformedV2,
			TransformedV0,
			Color
			);			
	}

	UFUNCTION(BlueprintCallable, Category = "Draw Shape")
	static void Quad(
		const UWorld* WorldContext,	
		const FVector& V0,
		const FVector& V1,
		const FVector& V2,
		const FVector& V3,
		const FColor& Color)
	{
		DrawDebugLine(
			WorldContext,
			V0,
			V0 + FVector::UpVector * 100.f,
			FColor::Magenta
			);

		DrawDebugLine(
			WorldContext,
			V1,
			V1 + FVector::UpVector * 100.f,
			FColor::Magenta
			);

		DrawDebugLine(
			WorldContext,
			V2,
			V2 + FVector::UpVector * 100.f,
			FColor::Magenta
			);

		DrawDebugLine(
			WorldContext,
			V3,
			V3 + FVector::UpVector * 100.f,
			FColor::Magenta
			);		
		
		DrawDebugLine(
			WorldContext,
			V0,
			V1,
			Color
			);

		DrawDebugLine(
			WorldContext,
			V1,
			V2,
			Color
			);

		DrawDebugLine(
			WorldContext,
			V2,
			V3,
			Color
			);

		DrawDebugLine(
			WorldContext,
			V3,
			V0,
			Color
			);
	}	
};
