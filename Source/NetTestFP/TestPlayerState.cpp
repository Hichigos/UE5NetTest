#include "TestPlayerState.h"

#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, Shots);
	DOREPLIFETIME(ATestPlayerState, Inventory);
}

void ATestPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPlayerState::IncreaseShots()
{
	if (!HasAuthority())
	{
		return;
	}
	
	Shots++;
}

void ATestPlayerState::AddItemToInventory(const int32 Id)
{
	const auto Slot = Inventory.FindByPredicate([&Id] (const auto& Item)
	{
		return Item.ItemId == Id;
	});

	if (Slot)
	{
		Slot->NumberOfItemsStored++;
		return;
	}

	const FInventorySlot NewSlot {Inventory.Num(), Id, 1};
	Inventory.Add(NewSlot);
}

void ATestPlayerState::ServerRequestIncreaseShots_Implementation()
{
	if (!HasAuthority())
	{
		return;
	}
	
	IncreaseShots();
}

bool ATestPlayerState::ServerRequestIncreaseShots_Validate()
{
	return true;
}
