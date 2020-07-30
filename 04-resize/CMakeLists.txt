cmake_minimum_required(VERSION 3.10)

project(resize)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

link_directories(/usr/local/lib)

add_executable(resize resize.cpp)

target_include_directories(resize PUBLIC /usr/local/include/opencv4)
target_link_libraries(resize PUBLIC opencv_highgui opencv_core opencv_imgcodecs opencv_imgproc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

