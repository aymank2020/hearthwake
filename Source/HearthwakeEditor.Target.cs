using UnrealBuildTool;
public class HearthwakeEditorTarget : TargetRules {
    public HearthwakeEditorTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("Hearthwake");
    }
}
