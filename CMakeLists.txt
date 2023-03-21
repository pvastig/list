cmake_minimum_required(VERSION 3.24)

project(list)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(lib/googletest)