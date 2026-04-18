// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExperimentTraversal : ModuleRules
{
	public ExperimentTraversal(ReadOnlyTargetRules Target) : base(Target)
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
			"ExperimentTraversal",
			"ExperimentTraversal/Variant_Platforming",
			"ExperimentTraversal/Variant_Platforming/Animation",
			"ExperimentTraversal/Variant_Combat",
			"ExperimentTraversal/Variant_Combat/AI",
			"ExperimentTraversal/Variant_Combat/Animation",
			"ExperimentTraversal/Variant_Combat/Gameplay",
			"ExperimentTraversal/Variant_Combat/Interfaces",
			"ExperimentTraversal/Variant_Combat/UI",
			"ExperimentTraversal/Variant_SideScrolling",
			"ExperimentTraversal/Variant_SideScrolling/AI",
			"ExperimentTraversal/Variant_SideScrolling/Gameplay",
			"ExperimentTraversal/Variant_SideScrolling/Interfaces",
			"ExperimentTraversal/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
