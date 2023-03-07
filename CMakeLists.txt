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
        src/Core/System/SystemManger.cpp include/Core/System/SystemManger.h include/Core/Events/EventBus.hpp include/Core/Events/EventHandel.hpp include/Core/Events/EventNoDataHandel.hpp src/Platform/OpenGL/OpenGL_Window.cpp include/Platform/OpenGL/OpenGL_Window.h src/Platform/Linux/Filesystem_Linux.cpp src/Platform/OSX/Metal_Window.cpp include/Platform/OSX/Metal_Window.h src/Platform/OSX/Filesystem_OSX.cpp src/Platform/Windows/Filesystem_Windows.cpp)

include_directories(
        include
        )

target_include_directories(Core PUBLIC
        include
        )

target_link_libraries(Core PUBLIC glfw glm)
