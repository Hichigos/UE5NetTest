#pragma once
#include "GameFramework/PlayerState.h"

#include "TestPlayerState.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	int32 SlotId;

	int32 ItemId;
	
	int32 NumberOfItemsStored;
};

UCLASS()
class ATestPlayerState final : public  APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void IncreaseShots();
	void AddItemToInventory(const int32 Id);

	int32 GetShots() const { return Shots; }
	TArray<FInventorySlot> GetInventory() { return Inventory; }

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void ServerRequestIncreaseShots();

protected:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = PlayerState)
	int32 Shots;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = PlayerState)
	TArray<FInventorySlot> Inventory;
};
