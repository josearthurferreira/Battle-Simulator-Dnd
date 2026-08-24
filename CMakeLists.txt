cmake_minimum_required(VERSION 3.14)
project(BattleSimulatorDnd CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
option(BUILD_PLATFORM_SDL "Build with SDL3 platform frontend" ON)

FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(entt)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

include_directories(include)

add_library(BattleSimulatorCore
    src/main.cpp
    src/battle_entity.cpp
    src/loader.cpp
    src/core.cpp
    src/sprite.cpp
    src/objects.cpp
)

target_link_libraries(BattleSimulatorCore PRIVATE
    EnTT::EnTT
    nlohmann_json::nlohmann_json
)

if(BUILD_PLATFORM_SDL)
    set(BUILD_SHARED_LIBS OFF)
    set(SDL_SHARED OFF)
    set(SDL_STATIC ON)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.14
    )
    FetchContent_MakeAvailable(SDL3)

    FetchContent_Declare(
        SDL3_TTF
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-3.2.2
    )
    FetchContent_MakeAvailable(SDL3_TTF)

    FetchContent_Declare(
        SDL3_IMAGE
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.4.4
    )
    FetchContent_MakeAvailable(SDL3_IMAGE)
    add_executable(BattleSimulator src/platform/sdl.cpp)
    target_link_libraries(BattleSimulator PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image
        BattleSimulatorCore
    )
endif()
