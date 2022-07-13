#pragma once
#include <GameFramework/PlayerController.h>

#include "TestPlayerController.generated.h"

UCLASS()
class ATestPlayerController final : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerApplyDamage(const float InDamage);
	
};
