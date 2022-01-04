cmake_minimum_required(VERSION 3.1)

project(raytracing LANGUAGES CXX VERSION 0.0.1)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

