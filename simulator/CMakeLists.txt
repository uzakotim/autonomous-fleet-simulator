# 1. Set the minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.15)

# 2. Define the project name and its programming language
project(MyProject LANGUAGES CXX)

# 3. Specify the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Create an executable target from your source code
add_executable(simulator src/main.cpp)