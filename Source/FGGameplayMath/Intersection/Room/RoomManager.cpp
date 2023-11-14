// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomManager.h"

void URoomManager::RegisterRoom(ARoomDemonstrator* Room)
{
	if(!Rooms.Contains(Room))
		Rooms.Add(Room);
}

ARoomDemonstrator* URoomManager::GetClosestRoom(const FVector& Location)
{
	auto ClosestDistance = TNumericLimits<float>::Max();
	ARoomDemonstrator* RoomCandidate = nullptr;

	for(const auto Room : Rooms)
	{
		if(Room->IsInsideRoom(Location))
		{
			const auto Distance = FVector::Distance(Location, Room->GetActorLocation());
			if(Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				RoomCandidate = Room;
			}
		}
	}

	return RoomCandidate;
}