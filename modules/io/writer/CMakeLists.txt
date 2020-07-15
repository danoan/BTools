cmake_minimum_required(VERSION 3.2)
project(lib-btools-writer)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-writer ${LIBRARY_ACTION}
        src/DataWriter.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(btools-writer scabolic)
endif()

target_include_directories(btools-writer PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/writer/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(btools-writer
        -lscabolic-energy)

set_target_properties(btools-writer PROPERTIES
        VERSION ${VERSION_BTOOLS_WRITER})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-writer
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)