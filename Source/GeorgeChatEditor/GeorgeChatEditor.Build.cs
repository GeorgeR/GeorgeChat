using UnrealBuildTool;

public class GeorgeChatEditor : ModuleRules
{
	public GeorgeChatEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
            });

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "EditorStyle",
                "EditorSubsystem",
				"Engine",
				"Slate",
				"SlateCore",
                "UnrealEd",
                "Projects",
				"InputCore",
				"ToolMenus",
			});
    }
}
