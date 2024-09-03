// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGeniusPlan : ModuleRules
{
	public TheGeniusPlan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "SlateCore", "HTTP", "Json", "JsonUtilities" });
        }
}
