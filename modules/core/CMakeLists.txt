cmake_minimum_required(VERSION 3.2)
project(btools-core)

add_library(btools-core
        src/BCApplication.cpp
        src/pool/ODRPool.cpp
        src/pool/FlowPool.cpp
        src/control/BCControl.cpp
        src/model/GMM.cpp)

target_include_directories(btools-core PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(btools-core
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lscabolic-core
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS}
        )