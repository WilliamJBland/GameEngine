cmake_minimum_required(VERSION 3.7)

# project name
project(GameEngine)

# Add SDL2 CMake modules

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# creates the variable EXEC and sets it to run.exe
set(EXEC GameEngine)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)


add_executable(${EXEC} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)




# Add SDL2 library
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)


# # # # Add SDL2_image library

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_LIBRARIES}
    )

target_link_libraries(GameEngine PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
