cmake_minimum_required(VERSION 3.14)
project(BattleSimulatorDnd CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

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

add_executable(BattleSimulator src/main.cpp src/battle_entity.cpp src/loader.cpp)

target_link_libraries(BattleSimulator PRIVATE EnTT::EnTT nlohmann_json::nlohmann_json)