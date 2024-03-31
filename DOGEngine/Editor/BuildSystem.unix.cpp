// BuildSystem.unix.cpp
#ifdef DOG_PLATFORM_UNIX
#include "BuildSystem.h"

BuildSystem::BuildSystem(const std::string& buildToolPath) : buildToolPath(buildToolPath) {
    // TODO
}

bool BuildSystem::compile(const std::string& projectPath, const std::string& additionalArguments, bool launchInNewWindow, bool keepWindowOpen) {
    // TODO
    return true;
}

bool BuildSystem::checkBuildToolExists() {
    // TODO
    return true;
}
#endif
