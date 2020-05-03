# This CMakeLists.txt file is just for providing IDE support for those requiring it (Clion for instance)
# The toolchain itself does not build with it - use the Makefile for that (see the readme).

cmake_minimum_required(VERSION 3.2)

project(toolchain C CXX)

set(COMMON_FLAGS "-W -Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-parentheses -Wno-pointer-sign -Wno-incompatible-pointer-types")
list(APPEND CMAKE_C_FLAGS "-std=c99 ${COMMON_FLAGS}")
list(APPEND CMAKE_CXX_FLAGS "-std=c++14 ${COMMON_FLAGS}")

set(INCLUDE_DIRECTORIES "")
include_directories(${CMAKE_SOURCE_DIR}/src/ce
                    ${CMAKE_SOURCE_DIR}/src/fatdrvce
                    ${CMAKE_SOURCE_DIR}/src/fileioc
                    ${CMAKE_SOURCE_DIR}/src/fontlibc
                    ${CMAKE_SOURCE_DIR}/src/graphx
                    ${CMAKE_SOURCE_DIR}/src/keypadc
                    ${CMAKE_SOURCE_DIR}/src/usbdrvce
                    ${CMAKE_SOURCE_DIR}/src/std)

file(GLOB_RECURSE SOURCE_FILES   src      true  *.h *.hpp *.c *.cpp)
file(GLOB_RECURSE EXAMPLES_FILES examples true  *.h *.hpp *.c *.cpp)

add_executable(toolchain ${SOURCE_FILES} ${EXAMPLES_FILES})
