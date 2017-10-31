cmake_minimum_required(VERSION 2.8)

file(GLOB ficSRC
	"*.h"
	"*.cpp"
)

project( VideoTool )
find_package( OpenCV REQUIRED )
add_executable( VideoTool ${ficSRC} )
target_link_libraries( VideoTool ${OpenCV_LIBS} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
