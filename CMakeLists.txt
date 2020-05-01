cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME TopDown)
project(${PROJECT_NAME})
link_libraries(stdc++fs) #link the filesystem

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp") #glob all the source files intp one place
file(GLOB REQ_DLLS "libs/required_dll/*.dll")
file(COPY ${REQ_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${REQUIRED_DLLS_FOR_SFML} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY libs/SFML-2.5.1/bin/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

include_directories("libs")
include_directories("libs/glad/include/")
include_directories("src/")
include_directories("libs/glm/glm/")
include_directories("src/Engine/")
include_directories("src/Engine/SpawnableObjects/")
include_directories("src/Engine/StateMachine/")
include_directories("src/Engine/Generators/")
include_directories("src/Engine/Manager/")

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} libs/glad/src/glad.c libs/FastNoise/FastNoise.cpp main.cpp)


target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system ${OPENGL_LIBRARIES} )
