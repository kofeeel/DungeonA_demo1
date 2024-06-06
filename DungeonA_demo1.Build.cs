// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class DungeonA_demo1 : ModuleRules
{
    public DungeonA_demo1(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

    }
}
