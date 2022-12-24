cmake_minimum_required(VERSION 3.10)
project(Photo2Point)

set(OpenCV_DIR "~/tmpSoft/opencv-4.6.0/build")
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Photo2Point main.cpp )
target_link_libraries( Photo2Point ${OpenCV_LIBS} )