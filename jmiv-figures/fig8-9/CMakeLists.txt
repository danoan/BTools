cmake_minimum_required(VERSION 3.2)
project(jmiv-fig8)


set(INCLUDE_DIRS
        include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

set(LINK_LIBS -lbtools-reader
        -lbtools-core
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

add_executable(jmiv-fig8 jmiv-fig8.cpp
        src/energyUtils.cpp
        src/countUnlabeled.cpp
        src/utils.cpp)

target_include_directories(jmiv-fig8 PRIVATE ${INCLUDE_DIRS})
target_link_libraries(jmiv-fig8 ${LINK_LIBS})

install(TARGETS jmiv-fig8
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)