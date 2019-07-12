cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "BTools binaries and libraries location." )
project(btools)


SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${BOOST_LIBS_DIR}:${DIPACUS_LIBS_DIR}:${SCABOLIC_LIBS_DIR}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build/lib CACHE PATH "DIPaCUS libraries location path.")

set(GEOC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "geoc include location path.")

set(SCABOLIC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "SCaBOliC include location path.")
set(SCABOLIC_LIBS_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build/lib CACHE PATH "SCaBOliC libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_APPLICATIONS ON CACHE BOOL "Build applications.")
set(BUILD_FIGURES ON CACHE BOOL "Build JMIV figures.")
set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Create shared libraries. If off, create static libraries.")

set(USE_LOCAL_REPOSITORIES ON CACHE BOOL "Pull external repositories from GitHub.")

if(${USE_LOCAL_REPOSITORIES})
    include(ext-projects/ExtProjects.cmake)
endif()

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")


link_directories(${DIPACUS_LIBS_DIR}
        ${GEOC_LIBS_DIR}
        ${SCABOLIC_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/reader
        )

add_subdirectory(modules/core)
add_subdirectory(modules/utils)
add_subdirectory(modules/reader)

if(${BUILD_TESTS})
    #add_subdirectory(modules/lab/Test)
endif()

if(${BUILD_APPLICATIONS})
    add_subdirectory(app/boundary-correction)
    add_subdirectory(app/export-seed-mask)
    add_subdirectory(app/grabcut)
    add_subdirectory(app/regions-of-interest)
    add_subdirectory(app/seed-selector)
    add_subdirectory(app/shape-flow)
    add_subdirectory(app/summary-flow)
endif()

if(${BUILD_FIGURES})
    add_subdirectory(jmiv-figures)
endif()


