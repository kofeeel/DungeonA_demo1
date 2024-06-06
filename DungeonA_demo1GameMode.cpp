// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonA_demo1GameMode.h"
#include "DungeonA_demo1Character.h"
#include "UObject/ConstructorHelpers.h"

ADungeonA_demo1GameMode::ADungeonA_demo1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
