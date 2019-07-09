cmake_minimum_required(VERSION 3.2)
project(jmiv-fig1)

add_executable(jmiv-fig1 jmiv-fig1.cpp)

target_include_directories(jmiv-fig1 PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(jmiv-fig1
        -lbtools-core
        -lbtools-reader
        -lbtools-utils
        -lscabolic-optimization
        -lscabolic-energy
        -lscabolic-core
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lexhaustive-gc-api
        -lexhaustive-gc-energy
        -lexhaustive-gc-core
        -lgcurve
        -lgcurve-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})