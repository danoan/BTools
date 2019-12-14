cmake_minimum_required(VERSION 3.2)
project(jmiv-fig2)

add_executable(jmiv-fig2 jmiv-fig2.cpp
        src/distance-transform.cpp
        src/glued-curve.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(jmiv-fig2 btools-core btools-reader btools-utils scabolic dipacus exhaustive-gc gcurve)
else()
    add_dependencies(jmiv-fig2 btools-core btools-reader btools-utils)
endif()

target_include_directories(jmiv-fig2 PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(jmiv-fig2
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

install(TARGETS jmiv-fig2
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)