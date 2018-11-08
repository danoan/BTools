cmake_minimum_required(VERSION 3.2)
project(btools)


#CMAKE_INSTALL_PREFIX: install location

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(GEOC_INCLUDE_DIRS /usr/local/include/geoc CACHE PATH "geoc include location path.")

set(SCABOLIC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "SCaBOliC include location path.")
set(SCABOLIC_LIBS_DIR /usr/local/lib CACHE PATH "SCaBOliC libraries location path.")

set(BINOCS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "BinOCS include location path.")
set(BINOCS_LIBS_DIR /usr/local/lib CACHE PATH "BinOCS libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")


link_directories(ext/lib
        ${CMAKE_PREFIX_PATH})


add_subdirectory(Applications/dataset)
add_subdirectory(Applications/fromSeed)
add_subdirectory(Applications/interactive)
add_subdirectory(Applications/multipleSelector)
add_subdirectory(Applications/flow)
add_subdirectory(Test)

