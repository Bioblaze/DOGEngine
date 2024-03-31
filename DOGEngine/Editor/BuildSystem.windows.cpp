// BuildSystem.windows.cpp
#ifdef DOG_PLATFORM_WINDOWS
#include "BuildSystem.h"
#include <iostream>
#include <windows.h>
#include "../Core/Logger.h"

BuildSystem::BuildSystem(const std::string& buildToolPath) : buildToolPath(buildToolPath) {
    if (!checkBuildToolExists()) {
        Logger::Get().DebugLog("Build tool does not exist at the specified path: {}", buildToolPath.c_str());
        // Consider appropriate error handling here.
    }
}

bool BuildSystem::compile(const std::string& projectPath, const std::string& additionalArguments, bool launchInNewWindow, bool keepWindowOpen) {
    if (projectPath.length() < 4 || projectPath.substr(projectPath.length() - 4) != ".sln") {
        Logger::Get().DebugLog("The specified project path does not point to a .sln file: {}", projectPath.c_str());
        return false;
    }

    if (GetFileAttributesA(projectPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        Logger::Get().DebugLog("The specified .sln file does not exist: {}", projectPath.c_str());
        return false;
    }

    if (!checkBuildToolExists()) {
        Logger::Get().DebugLog("Build tool does not exist or the path is not set correctly: {}", buildToolPath.c_str());
        return false;
    }

    Logger::Get().DebugLog("Using build tool path: {}", buildToolPath.c_str());
    Logger::Get().DebugLog("Project path: {}", projectPath.c_str());
    Logger::Get().DebugLog("Additional arguments: {}", additionalArguments.c_str());

    std::string commandLine;
    if (launchInNewWindow) {
        if (keepWindowOpen) {
            // Correctly handle quotes for cmd /K
            commandLine = "cmd /K \"\"" + buildToolPath + "\" \"\"" + projectPath + "\"\" " + additionalArguments + "\"";
        }
        else {
            commandLine = "cmd /C \"\"" + buildToolPath + "\" \"\"" + projectPath + "\"\" " + additionalArguments + "\" & pause";
        }
    }
    else {
        commandLine = "\"" + buildToolPath + "\" \"\"" + projectPath + "\"\" " + additionalArguments;
    }

    Logger::Get().DebugLog("Executing command line: {}", commandLine.c_str());

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD flags = launchInNewWindow ? CREATE_NEW_CONSOLE : 0;

    if (!CreateProcessA(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, FALSE, flags, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return false;
    }

    if (launchInNewWindow && !keepWindowOpen) {
        // Wait until the build process exits, only if we're not keeping the window open.
        WaitForSingleObject(pi.hProcess, INFINITE);
    }

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

bool BuildSystem::checkBuildToolExists() {
    DWORD dwAttrib = GetFileAttributesA(buildToolPath.c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
#endif
