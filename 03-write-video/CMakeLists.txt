cmake_minimum_required(VERSION 3.10)

project(image)

set(CMAKE_CXX_FLAGS "-std=c++11")

link_directories(/usr/local/lib)

add_executable(write write.cpp)
target_include_directories(write PUBLIC /usr/local/include/opencv4)
target_link_libraries(write PUBLIC
                      opencv_highgui
                      opencv_core
                      opencv_imgcodecs
                      opencv_imgproc
                      opencv_videoio)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

