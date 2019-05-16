cmake_minimum_required(VERSION 3.2)
project(regions-of-interest)

add_executable(regions-of-interest regions-of-interest.cpp
        src/InputReader.cpp)

add_dependencies(shape-flow btools-core btools-utils)

target_include_directories(regions-of-interest PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(regions-of-interest
        -lbtools-core
        -lscabolic-core
        -lscabolic-optimization
        -lscabolic-energy
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

INSTALL(TARGETS regions-of-interest
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)