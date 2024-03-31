cmake_minimum_required(VERSION 3.14) # Ensure compatibility with CMake 3.14 or later

project(dog-engine LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Show all commands
set(CMAKE_VERBOSE_MAKEFILE on)

# Find packages required for the project
find_package(cereal CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Include the SDL2 bindings and OpenGL3 bindings for ImGui as specified in the dependencies
# This assumes that the imgui package has been set up with the sdl2-binding, opengl3-binding, and sdl2-renderer-binding features enabled through vcpkg or other package management systems.

# Main executable
add_executable(dog-engine
  DOGEngine/DOGEngine.cpp
)

# Add subdirectories for each component of the project
add_subdirectory(DOGEngine/Client)
add_subdirectory(DOGEngine/Core)
add_subdirectory(DOGEngine/Editor)
add_subdirectory(DOGEngine/Server)

# TODO: Use target platform instead, who knows, maybe someone
# is trying to cross-compile DOGEngine...

if(WIN32)
  add_definitions(-DDOG_PLATFORM_WINDOWS)
else()
  add_definitions(-DDOG_PLATFORM_UNIX)
endif()

# Link libraries with the main executable
target_link_libraries(dog-engine
  PRIVATE cereal::cereal
  PRIVATE EnTT::EnTT
  PRIVATE fmt::fmt # If using header-only, replace fmt::fmt with fmt::fmt-header-only
  PRIVATE ${OPENGL_LIBRARIES}
  PRIVATE GLEW::GLEW
  PRIVATE glfw
  PRIVATE glm::glm # If using header-only, replace glm::glm with glm::glm-header-only
  PRIVATE SDL2::SDL2 SDL2::SDL2main # SDL2 static or dynamic as available
  PRIVATE imgui::imgui
  # PRIVATE SDL2_image::SDL2_image # SDL2_image static or dynamic as available, with libjpeg-turbo feature
  PRIVATE SDL2_mixer::SDL2_mixer # SDL2_mixer static or dynamic as available, with mpg123 feature
)

# Include directories
target_include_directories(dog-engine PRIVATE ${OPENGL_INCLUDE_DIR})
