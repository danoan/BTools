cmake_minimum_required(VERSION 3.2)
project(btools)


#CMAKE_INSTALL_PREFIX: install location

find_package(DGtal 0.9 REQUIRED)
find_package(OpenCV 3.3.0 REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "Include directory of Digital Processing Primitive Library.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "Libraries directory of Digital Processing Primitive Library.")

set(GEOC_INCLUDE_DIRS /usr/local/include/geoc CACHE PATH "Include directory of Geometric Estimators Library.")

set(SCABOLIC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "Include directory of Energy Optimization Library.")
set(SCABOLIC_LIBS_DIR /usr/local/lib CACHE PATH "Libraries directory of Energy Optimization Library.")

set(BINOCS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "Include directory of Segmentation and Flow Library.")
set(BINOCS_LIBS_DIR /usr/local/lib CACHE PATH "Libraries directory of Segmentation and Flow Library.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")


link_directories(ext/lib
        ${CMAKE_PREFIX_PATH})


add_subdirectory(Applications/dataset)
add_subdirectory(Applications/fromSeed)
add_subdirectory(Applications/interactive)
add_subdirectory(Applications/multipleSelector)
add_subdirectory(Applications/flow)
add_subdirectory(Test)

