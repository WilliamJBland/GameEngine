cmake_minimum_required(VERSION 3.7)

# project name
project(GameEngine)

# creates the variable EXEC and sets it to run.exe
set(EXEC GameEngine)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)



# I../includes
include_directories(includes)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)


find_package(SDL2 REQUIRED)

add_executable(${EXEC} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)
