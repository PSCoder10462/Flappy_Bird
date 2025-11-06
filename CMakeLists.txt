cmake_minimum_required(VERSION 3.22)

# Define the project and executable name as a variable for consistency
set(PROJECT_NAME "Flappy_Bird")
project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include FetchContent for SDL3
include(FetchContent)

# Path where SDL3 will be stored
set(SDL3_SOURCE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/sdl3)

if (NOT EXISTS "${SDL3_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "Fetching SDL3 into thirdparty/sdl3...")
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.24
        SOURCE_DIR ${SDL3_SOURCE_DIR}
    )
    FetchContent_Populate(SDL3)
else()
    message(STATUS "Using existing thirdparty/sdl3 directory")
endif()

# Add SDL3 as a subproject (don’t install it globally)
add_subdirectory(${SDL3_SOURCE_DIR} ${CMAKE_BINARY_DIR}/sdl3_build EXCLUDE_FROM_ALL)

# Collect all .cpp files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include your headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)