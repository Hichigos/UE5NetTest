// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetTestFPGameMode.generated.h"

UCLASS(minimalapi)
class ANetTestFPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetTestFPGameMode();

	virtual void Tick(float DeltaSeconds) override;

private:

	float DebugMessageDelay = 3.f;
	float ElapsedTime = 0.f;
};



