cmake_minimum_required(VERSION 3.12)
project(lab1_5)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lab1_5 src/perspective.cpp)

target_link_libraries(lab1_5 ${OpenCV_LIBS})

set_target_properties(lab1_5 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
