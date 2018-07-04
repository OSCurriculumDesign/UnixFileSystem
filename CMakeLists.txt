cmake_minimum_required(VERSION 3.1)

project(unix_file_sys)

set(CMAKE_CXX_STANDARD 11)

FILE(GLOB HEADER_LIST "header/*.h")
FILE(GLOB SOURCE_LIST "cpp/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/header)

add_executable(unix_file_sys main.cpp ${SOURCE_DIR})