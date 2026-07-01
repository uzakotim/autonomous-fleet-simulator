# 1. Set the minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.15)

# 2. Define the project name and its programming language
project(simulator LANGUAGES CXX)

# 3. Specify the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Create an executable target from your source code
add_executable(
	simulator 
	src/main.cpp 
	src/Vehicle.cpp 
	src/Vehicle.h 
	src/State.h
    src/Controller.cpp
    src/Controller.h
    src/Logger.cpp
    src/Logger.h
    src/Sensor.cpp
    src/Sensor.h
    src/FleetManager.cpp
    src/FleetManager.h
    src/CollisionManager.cpp
    src/CollisionManager.h
    src/Map.h
    src/Point.h

)