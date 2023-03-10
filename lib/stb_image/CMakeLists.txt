#cmake_minimum_required(VERSION 3.16)

add_library( stb_image STATIC
        #cpp
        src/stb_image.cpp
        #h
        src/stb_image.h
        )

target_include_directories(stb_image PUBLIC
        src
        )
