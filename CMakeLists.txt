cmake_minimum_required(VERSION 3.14)
project(BattleSimulatorDnd CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)

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

add_executable(BattleSimulator src/main.cpp src/battle_entity.cpp src/loader.cpp src/platform/sdl.cpp src/core.cpp)

include_directories(include)

target_link_libraries(BattleSimulator PRIVATE EnTT::EnTT nlohmann_json::nlohmann_json SDL3::SDL3 SDL3_ttf::SDL3_ttf)
