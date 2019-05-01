cmake_minimum_required(VERSION 3.2)
project(btools-utils)

add_library(btools-utils
        src/dispUtils.cpp
        src/DataWriter.cpp
        src/imgUtils.cpp
        src/strUtils.cpp)

target_include_directories(btools-utils PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(btools-utils
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})