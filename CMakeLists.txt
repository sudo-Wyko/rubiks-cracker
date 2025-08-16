cmake_minimum_required(VERSION 3.12)
project("RubiksCracker" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 4.0 REQUIRED) # Adjust version if needed

add_executable(${PROJECT_NAME} 
    src/rubiks-cracker.cpp
    src/rubiks.cpp
    src/solver.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)



