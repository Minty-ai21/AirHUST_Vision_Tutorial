cmake_minimum_required(VERSION 3.10)
project(lab1_3)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(lab1_3 
    src/image_restoration.cpp
)

target_link_libraries(lab1_3 ${OpenCV_LIBS})

set_target_properties(lab1_3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
