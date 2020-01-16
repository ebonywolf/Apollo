cmake_minimum_required ( VERSION 3.3 )
project(Apollo)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(BUILD_LIBS ${BUILD_LIBS} "-lpthread -ljsoncpp")

file(GLOB lib_srcs *.* Include/*/* )

include_directories( Include/ )

add_executable(Apollo main.cpp ${lib_srcs} )


target_link_libraries( Apollo ${BUILD_LIBS} ) 


