# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Gallows)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(
    ../Gallows
)

# Add source files
file(GLOB SOURCES ../Gallows/*.cpp)

# Add resource file (icon)
if(WIN32)
    set(APP_ICON_RESOURCE "app_icon.rc")
    list(APPEND SOURCES ${APP_ICON_RESOURCE})
endif()

# Combine all source files
set(SOURCES
    ${SOURCES}
)

# Add the executable
add_executable(Gallows ${SOURCES})

# Specify output directory for the executable
set_target_properties(Gallows PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.."
)