// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class FourthWall : ModuleRules
{
	public FourthWall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI", "RenderCore", "ShaderCore", "OpenCV" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        LoadOpenCV();
	}

    public bool LoadOpenCV()
    {
        // Start OpenCV linking here

        // Create OpenCV Path 
        string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");
        bool isLibrarySupported = true;

        // Get Library Path 
        string LibPath = "";

        if (isLibrarySupported)
        {
            //Add Include path 
            PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            //Add Static Libraries
            PublicAdditionalLibraries.Add("opencv_world320.lib");

            //Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("opencv_world320.dll");
            PublicDelayLoadDLLs.Add("opencv_ffmpeg320_64.dll");
        }

        Definitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../ThirdParty/")); }
    } 
}
