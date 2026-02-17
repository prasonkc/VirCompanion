cmake_minimum_required(VERSION 3.20)
project(VPet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
add_executable(Main 
    src/main.cpp
    src/App.cpp
    src/Animation.cpp
)

target_link_directories(Main PRIVATE src)
target_link_libraries(Main PRIVATE SDL2::SDL2)