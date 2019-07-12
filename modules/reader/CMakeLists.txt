cmake_minimum_required(VERSION 3.2)
project(lib-btools-reader)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-reader ${LIBRARY_ACTION}
        src/DCFReader.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(btools-reader scabolic)
endif()

target_include_directories(btools-reader PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-reader
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)