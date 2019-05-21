cmake_minimum_required(VERSION 3.2)
project(btools)


#CMAKE_INSTALL_PREFIX: install location

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(GEOC_INCLUDE_DIRS /usr/local/include/geoc CACHE PATH "geoc include location path.")

set(SCABOLIC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "SCaBOliC include location path.")
set(SCABOLIC_LIBS_DIR /usr/local/lib CACHE PATH "SCaBOliC libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_APPLICATIONS OFF CACHE BOOL "Build applications.")
set(CREATE_SHARED_LIBRARIES OFF CACHE BOOL "Create shared libraries. If off, create static libraries.")


link_directories(${DIPACUS_LIBS_DIR}
        ${GEOC_LIBS_DIR}
        ${SCABOLIC_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/visitors
        ${CMAKE_BINARY_DIR}/modules/reader)

add_subdirectory(modules/core)
add_subdirectory(modules/utils)
add_subdirectory(modules/reader)
add_subdirectory(modules/visitors)

if(${BUILD_TESTS})
    #add_subdirectory(modules/lab/Test)
endif()

if(${BUILD_APPLICATIONS})
    add_subdirectory(modules/Applications/grabcut)
    add_subdirectory(modules/Applications/seed-selector)
    add_subdirectory(modules/Applications/boundary-correction)
    add_subdirectory(modules/Applications/shape-flow)
    add_subdirectory(modules/Applications/summary-flow)
    add_subdirectory(modules/Applications/regions-of-interest)
    add_subdirectory(modules/Applications/export-seed-mask)
endif()


