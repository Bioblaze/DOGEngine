// BuildSystem.h
#ifndef BUILDSYSTEM_H
#define BUILDSYSTEM_H

#include <string>

class BuildSystem {
public:
    explicit BuildSystem(const std::string& buildToolPath);
    bool compile(const std::string& projectPath, const std::string& additionalArguments, bool launchInNewWindow = false, bool keepWindowOpen = false);


private:
    std::string buildToolPath;
    bool checkBuildToolExists();
};

#endif // BUILDSYSTEM_H
