cmake_minimum_required(VERSION 3.2)
project(jmiv-figR1)

add_executable(jmiv-figR1 jmiv-figR1.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(jmiv-figR1 btools-core btools-reader btools-utils scabolic dipacus exhaustive-gc gcurve)
else()
    add_dependencies(jmiv-figR1 btools-core btools-reader btools-utils)
endif()

target_include_directories(jmiv-figR1 PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(jmiv-figR1
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
        -lexhaustive-gc-core
        -lexhaustive-gc-energy
        -lgcurve
        -lgcurve-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS jmiv-figR1
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)