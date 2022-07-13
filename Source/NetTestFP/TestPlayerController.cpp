#include "TestPlayerController.h"

#include "NetTestFPCharacter.h"

void ATestPlayerController::ServerApplyDamage_Implementation(const float InDamage)
{
	if (IsValid(GetPawn()))
	{
		const auto TestCharacter = CastChecked<ANetTestFPCharacter>(GetPawn());
		TestCharacter->ApplyDamage(InDamage);
	}
}

bool ATestPlayerController::ServerApplyDamage_Validate(const float InDamage)
{
	return true;
}
