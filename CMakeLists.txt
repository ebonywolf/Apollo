cmake_minimum_required ( VERSION 3.3 )
project(Apollo)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(BUILD_LIBS ${BUILD_LIBS} "-lpthread -ljsoncpp")

file(GLOB lib_srcs *.* Include/Core/*.* Include/Core/*/*.* Include/*.* )

Include_directories( Include/ Include/Core )

add_executable(Apollo main.cpp ${lib_srcs} )


target_link_libraries( Apollo ${BUILD_LIBS} ) 


