// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChallengeAcepted3 : ModuleRules
{
	public ChallengeAcepted3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
