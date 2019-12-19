cmake_minimum_required(VERSION 3.2)
project(jmiv-fig11-12)


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
        -lgcurve
        -lgcurve-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

add_executable(jmiv-fig11-12 jmiv-fig10-11.cpp
        src/energyUtils.cpp
        src/countUnlabeled.cpp
        src/utils.cpp)

add_dependencies(jmiv-fig11-12 btools-core btools-utils)

target_include_directories(jmiv-fig11-12 PRIVATE ${INCLUDE_DIRS})
target_link_libraries(jmiv-fig11-12 ${LINK_LIBS})

install(TARGETS jmiv-fig11-12
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)