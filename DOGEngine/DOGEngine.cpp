// DOGEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Core/Logger.h" 
#include "Editor/BuildSystem.h"


int main()
{
    Logger& appLogger = Logger::Get();
    appLogger.SetConfig("defaultLog.log", true);

    appLogger.Log("Hello World!");  // Log a simple message

    std::string timeString = appLogger.GetTimestamp();

    // Log with current time using DebugLog
    appLogger.DebugLog("Hello with fmt! Current time: %s", timeString.c_str());


    std::string buildToolPath = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe";
    BuildSystem buildSystem(buildToolPath);
    std::string projectPath = "E:\\DivineGames\\DungeonEngine\\DOGEngine\\DOGEngine.sln";
    std::string additionalArguments = "/p:Configuration=Debug /p:Platform=x64";

    if (buildSystem.compile(projectPath, additionalArguments, true, true)) {
        std::cout << "Build succeeded." << std::endl;
    }
    else {
        std::cout << "Build failed." << std::endl;
    }

    appLogger.Log("Press Enter to close the application...");
    std::cin.get();  // Wait for the user to press Enter

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
