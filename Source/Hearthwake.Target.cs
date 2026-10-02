using UnrealBuildTool;
public class HearthwakeTarget : TargetRules {
    public HearthwakeTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("Hearthwake");
    }
}
