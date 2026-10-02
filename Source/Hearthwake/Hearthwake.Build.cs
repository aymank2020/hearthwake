using UnrealBuildTool;
using System.IO;
public class Hearthwake : ModuleRules {
    public Hearthwake(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Core")));
        bEnableExceptions = true;
    }
}
