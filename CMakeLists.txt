# This CMakeLists.txt file is just for providing IDE support for those requiring it (Clion for instance)
# The toolchain itself does not build with it - use the Makefile for that (see the readme).

cmake_minimum_required(VERSION 3.2)

project(toolchain)

list(APPEND CMAKE_C_FLAGS "-std=c99 -W -Wall -Wno-incompatible-library-redeclaration -Wno-parentheses -Wno-pointer-sign -Wno-incompatible-pointer-types")

include_directories(${CMAKE_SOURCE_DIR}/src/ce
                    ${CMAKE_SOURCE_DIR}/src/fatdrvce
                    ${CMAKE_SOURCE_DIR}/src/fileioc
                    ${CMAKE_SOURCE_DIR}/src/fontlibc
                    ${CMAKE_SOURCE_DIR}/src/graphx
                    ${CMAKE_SOURCE_DIR}/src/keypadc
                    ${CMAKE_SOURCE_DIR}/src/textioc
                    ${CMAKE_SOURCE_DIR}/src/usbdrvce
                    ${CMAKE_SOURCE_DIR}/src/std
                    ${CMAKE_SOURCE_DIR}/src/compatibility)

file(GLOB_RECURSE SOURCE_FILES   src      false *.h *.c)
file(GLOB_RECURSE EXAMPLES_FILES examples false *.h *.c)

add_executable(toolchain ${SOURCE_FILES} ${EXAMPLES_FILES})
