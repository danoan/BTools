cmake_minimum_required(VERSION 3.2)
project(multipleselector-application)

add_executable(multipleSelector
        multipleSelector.cpp
        src/InputReader.cpp
        src/MultipleSelectorControl.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/DataReader.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/DataWriter.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/strUtils.cpp)

target_compile_definitions(multipleSelector PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(multipleSelector PRIVATE cxx_auto_type)
target_compile_options(multipleSelector PRIVATE -fext-numeric-literals)

target_include_directories(multipleSelector PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BINOCS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(multipleSelector
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
