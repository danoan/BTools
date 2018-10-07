cmake_minimum_required(VERSION 3.2)
project(btools-fromseed)

add_executable(fromseed
        fromSeed.cpp
        src/FromSeedControl.cpp
        src/InputReader.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/strUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/imgUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/DataReader.cpp)

target_compile_definitions(fromseed PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(fromseed PRIVATE cxx_auto_type)
target_compile_options(fromseed PRIVATE -fext-numeric-literals)

target_include_directories(fromseed PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BINOCS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(fromseed
        -lbinocs-application
        -lscabolic-energy
        -lscabolic-core
        -lscabolic-optimization
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
