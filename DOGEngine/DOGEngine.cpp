// DOGEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include "Core/Logger.h" 
#include "Core/Renderer.h"
#include "Editor/BuildSystem.h"
#include "imgui.h"

int main(int argc, char* args[])
{
    Logger& appLogger = Logger::Get();
    appLogger.SetConfig("defaultLog.log", true);

    appLogger.Log("Hello World!");  // Log a simple message

    std::string timeString = appLogger.GetTimestamp();

    // Log with current time using DebugLog
    appLogger.DebugLog("Hello with fmt! Current time: %s", timeString.c_str());

    try {
        Renderer& renderer = Renderer::getInstance();
        renderer.CreateWindow("Hello World", 800, 600);
        bool running = true;
        SDL_Event e;

        // Initial player state, adjust as necessary
        renderer.player.x = 22; // Player's starting X position
        renderer.player.y = 12; // Player's starting Y position
        renderer.player.angle = 0; // Player's starting view angle
        while (running) {
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }


            renderer.Prepare2DRender(); // Prepare renderer for drawing 2D content

            renderer.Render3DView(); // Render the 3D view using raycasting

            // Clear screen with a color
            //SDL_SetRenderDrawColor(renderer.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF); // White
            //SDL_RenderClear(renderer.GetRenderer());

            // Game loop content here, drawing operations...

            // Update screen
            //SDL_RenderPresent(renderer.GetRenderer());
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    appLogger.Log("Press Enter to close the application...");
    std::cin.get();  // Wait for the user to press Enter

    return 0;
}
//std::string buildToolPath = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe";
//BuildSystem buildSystem(buildToolPath);
//std::string projectPath = "E:\\DivineGames\\DungeonEngine\\DOGEngine\\DOGEngine.sln";
//std::string additionalArguments = "/p:Configuration=Debug /p:Platform=x64";

//if (buildSystem.compile(projectPath, additionalArguments, true, true)) {
//    std::cout << "Build succeeded." << std::endl;
//}
//else {
//    std::cout << "Build failed." << std::endl;
//}