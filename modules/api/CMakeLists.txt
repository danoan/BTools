cmake_minimum_required(VERSION 3.2)
project(lib-btools-api)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-api ${LIBRARY_ACTION}
        src/api.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies( btools-api dipacus scabolic)
endif()

target_include_directories(btools-api PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(btools-api
        -ldipacus-components
        -ldipacus-base
        -lscabolic-core
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

set_target_properties(btools-api PROPERTIES
        VERSION ${VERSION_BTOOLS_API})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-api
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)