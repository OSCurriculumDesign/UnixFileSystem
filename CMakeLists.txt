cmake_minimum_required(VERSION 3.1)

project(unix_file_sys)

set(CMAKE_CXX_STANDARD 11)

FILE(GLOB HEADER_LIST "header/*.h")
FILE(GLOB SOURCE_LIST "cpp/*.cpp")

# find_package( ZLIB REQUIRED )
# if ( ZLIB_FOUND )
#     include_directories( ${ZLIB_INCLUDE_DIRS} )
#     target_link_libraries( unix_file_sys ${ZLIB_LIBRARIES} )
# endif( ZLIB_FOUND )

include_directories(${CMAKE_SOURCE_DIR}/header)

add_executable(unix_file_sys main.cpp ${SOURCE_LIST})