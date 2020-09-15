cmake_minimum_required(VERSION 3.2)

set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext-projects/source)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-release)
else()
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-debug)
endif ()

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "DIPaCUS libraries location path.")

set(GEOC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "geoc include location path.")

set(SCABOLIC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "SCaBOliC include location path.")
set(SCABOLIC_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "SCaBOliC libraries location path.")

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "BTools binaries and libraries install location." )
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${BOOST_LIBS_DIR}:${DIPACUS_LIBS_DIR}:${SCABOLIC_LIBS_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(USE_REMOTE_REPOSITORIES ON CACHE BOOL "Pull external repositories from GitHub.")
set(BUILD_APPLICATIONS ON CACHE BOOL "Build applications.")
set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Create shared libraries. If off, create static libraries.")

set(SELECTED_FEATURES "ALL" CACHE STRING "Option SEED_SELECTION builds modules for seed selection;ALL builds everything")

project(btools)

set(VERSION_BTOOLS_CORE master)
set(VERSION_BTOOLS_UTILS master)
set(VERSION_BTOOLS_WRITER master)
set(VERSION_BTOOLS_SEEDIO master)
set(VERSION_BTOOLS_API master)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

if(${USE_REMOTE_REPOSITORIES})
    include(ext-projects/ExtProjects.cmake)
endif()


link_directories(${DIPACUS_LIBS_DIR}
        ${GEOC_LIBS_DIR}
        ${SCABOLIC_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/io/reader
        ${CMAKE_BINARY_DIR}/modules/io/writer
        ${CMAKE_BINARY_DIR}/modules/io/seed
        ${CMAKE_BINARY_DIR}/modules/api
        )

if(${SELECTED_FEATURES} STREQUAL "SEED_SELECTION")
    add_subdirectory(modules/utils)
    add_subdirectory(modules/io/seed)

    if(${BUILD_APPLICATIONS})
        add_subdirectory(app/export-seed-mask)
        add_subdirectory(app/grabcut)
        add_subdirectory(app/seed-selector)
        add_subdirectory(app/summary-flow)
    endif()

elseif(${SELECTED_FEATURES} STREQUAL "ALL")
    add_subdirectory(modules/utils)
    add_subdirectory(modules/io/writer)
    add_subdirectory(modules/io/seed)
    add_subdirectory(modules/core)
    add_subdirectory(modules/api)

    if(${BUILD_APPLICATIONS})
        add_subdirectory(app/boundary-correction)
        add_subdirectory(app/export-seed-mask)
        add_subdirectory(app/grabcut)
        add_subdirectory(app/regions-of-interest)
        add_subdirectory(app/seed-selector)
        add_subdirectory(app/shape-flow)
        add_subdirectory(app/summary-flow)
    endif()

endif()






