cmake_minimum_required(VERSION 3.10)

project(PusoyDos)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
add_compile_options(-O0)

find_package(SFML 2 COMPONENTS graphics graphics audio REQUIRED)

file(GLOB SOURCES "*.cpp")

include_directories(
    ${SFML_INCLUDE_DIR}
)

add_executable(pusoy_dos ${SOURCES})
target_link_libraries(pusoy_dos sfml-graphics sfml-audio)