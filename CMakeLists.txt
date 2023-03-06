cmake_minimum_required(VERSION 3.22)
project(Core)

set(CMAKE_CXX_STANDARD 20)

#libs
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only")
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

file(GLOB_RECURSE SRC
        src/*.h
        src/*.hpp
        src/*.cpp
        )

file(GLOB_RECURSE INCLUDE
        Include/*.h
        Include/*.hpp
        Include/*.cpp
        )

add_library(Core
        ${SRC}
        ${INCLUDE}
        src/Core/ECS/Component_Pool.hpp src/Core/ECS/View.hpp src/Core/ECS/FastView.hpp)

target_include_directories(Core PUBLIC
        include
        src
        )

target_link_libraries(Core PUBLIC glfw glm)