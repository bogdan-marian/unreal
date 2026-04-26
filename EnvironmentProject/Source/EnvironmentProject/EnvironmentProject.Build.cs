// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EnvironmentProject : ModuleRules
{
	public EnvironmentProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"EnvironmentProject",
			"EnvironmentProject/Variant_Platforming",
			"EnvironmentProject/Variant_Platforming/Animation",
			"EnvironmentProject/Variant_Combat",
			"EnvironmentProject/Variant_Combat/AI",
			"EnvironmentProject/Variant_Combat/Animation",
			"EnvironmentProject/Variant_Combat/Gameplay",
			"EnvironmentProject/Variant_Combat/Interfaces",
			"EnvironmentProject/Variant_Combat/UI",
			"EnvironmentProject/Variant_SideScrolling",
			"EnvironmentProject/Variant_SideScrolling/AI",
			"EnvironmentProject/Variant_SideScrolling/Gameplay",
			"EnvironmentProject/Variant_SideScrolling/Interfaces",
			"EnvironmentProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
