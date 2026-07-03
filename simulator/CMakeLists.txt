cmake_minimum_required(VERSION 3.15)

project(simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  tinyxml2
  GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
  GIT_TAG 10.0.0
)
FetchContent_MakeAvailable(tinyxml2)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(
  simulator
  src/main.cpp
  src/Vehicle.cpp
  src/Controller.cpp
  src/Logger.cpp
  src/Sensor.cpp
  src/FleetManager.cpp
  src/CollisionManager.cpp
  src/map/Graph.cpp
  src/map/OSMParser.cpp
)

target_include_directories(simulator PRIVATE src src/map)

target_link_libraries(simulator PRIVATE tinyxml2::tinyxml2)

add_executable(
  simulator_tests
  src/tests/graph_test.cpp
  src/tests/astar_test.cpp
  src/tests/route_follower_test.cpp
  src/map/Graph.cpp
  src/map/OSMParser.cpp
  src/Vehicle.cpp
  src/Controller.cpp
  src/Sensor.cpp
)

target_include_directories(simulator_tests PRIVATE src src/map)
target_link_libraries(simulator_tests PRIVATE tinyxml2::tinyxml2 Catch2::Catch2WithMain)

enable_testing()
add_test(NAME simulator_tests COMMAND simulator_tests)
