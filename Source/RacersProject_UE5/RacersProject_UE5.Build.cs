// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RacersProject_UE5 : ModuleRules
{
	public RacersProject_UE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara", "Slate", "SlateCore" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Json", "Niagara"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
