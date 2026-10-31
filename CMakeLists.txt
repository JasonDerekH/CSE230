cmake_minimum_required(VERSION 3.16)
project(howitzer_physics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(howitzer_physics
   main.cpp
   acceleration.cpp
   ground.cpp
   position.cpp
   projectile.cpp
   velocity.cpp
)

target_include_directories(howitzer_physics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
