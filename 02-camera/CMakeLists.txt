cmake_minimum_required(VERSION 3.10)

project(image)

set(CMAKE_CXX_FLAGS "-std=c++11")

link_directories(/usr/local/lib)

add_executable(capture capture.cpp)
target_include_directories(capture PUBLIC /usr/local/include/opencv4)
target_link_libraries(capture PUBLIC
                      opencv_highgui
                      opencv_core
                      opencv_imgcodecs
                      opencv_videoio)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

