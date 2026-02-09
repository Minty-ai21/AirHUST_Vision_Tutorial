cmake_minimum_required(VERSION 3.10)
project(lab2_2)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(lab2_2 
    src/main.cpp 
    src/image_restoration.cpp
)

target_link_libraries(lab2_2 ${OpenCV_LIBS})

set_target_properties(lab2_2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
