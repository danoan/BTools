cmake_minimum_required(VERSION 3.2)
project(binocs-utils)

add_library(binocs-utils
        src/dispUtils.cpp
        src/DataWriter.cpp
        src/imgUtils.cpp
        src/strUtils.cpp)

target_include_directories(binocs-utils PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(binocs-utils
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})