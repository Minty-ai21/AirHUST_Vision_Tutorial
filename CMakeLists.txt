cmake_minimum_required(VERSION 3.10)
project(lab1_4)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lab1_4 src/spin.cpp
                      src/spin_improve.cpp)

target_link_libraries(lab1_4 ${OpenCV_LIBS})

set_target_properties(lab1_4 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(lab1_4 stdc++fs)
endif()
