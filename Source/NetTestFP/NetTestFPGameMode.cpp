// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetTestFPGameMode.h"
#include "NetTestFPCharacter.h"
#include "TestPlayerController.h"
#include "TestPlayerState.h"
#include "GameFramework/GameState.h"
#include "UObject/ConstructorHelpers.h"

ANetTestFPGameMode::ANetTestFPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	PrimaryActorTick.bCanEverTick = true;
}

void ANetTestFPGameMode::Tick(float DeltaSeconds)
{
	if (ElapsedTime < DebugMessageDelay)
	{
		ElapsedTime += DeltaSeconds;
		return;
	}
	
	for (const auto& PS : GameState->PlayerArray)
	{
		const auto PlayerState = Cast<ATestPlayerState>(PS);
		const auto PlayerController = CastChecked<ATestPlayerController>(PlayerState->GetPlayerController());
		if (!ensure(PlayerController))
		{
			return;
		}
		
		const auto Pawn = CastChecked<ANetTestFPCharacter>(PlayerController->GetPawn());
		if(GEngine && PlayerState && Pawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
			FString::Printf(TEXT("Player %s, Shots fired: %i"),
				*PlayerState->GetName(),
				PlayerState->GetShots()));

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
		FString::Printf(TEXT("Player %s, Health left: %i"),
				*PlayerState->GetName(),
				Pawn->GetHealth()));

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
		FString::Printf(TEXT("Player %s, Inventory slots occupied: %i"),
				*PlayerState->GetName(),
			PlayerState->GetInventory().Num()));

			for (const auto& [SlotId, ItemId, NumberOfItemsStored] : PlayerState->GetInventory())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
				FString::Printf(TEXT("Player %s, Slot id: %i, Item id: %i, Number of items stored: %i"),
				*PlayerState->GetName(),
				SlotId,
				ItemId,
				NumberOfItemsStored));
			}

		}
	}

	ElapsedTime = 0.f;
	
	Super::Tick(DeltaSeconds);
}
