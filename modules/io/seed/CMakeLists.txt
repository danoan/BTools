cmake_minimum_required(VERSION 3.2)
project(lib-btools-seedio)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-seedio ${LIBRARY_ACTION}
        src/GrabCutIO.cpp)

target_include_directories(btools-seedio PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include)

set_target_properties(btools-seedio PROPERTIES
        VERSION ${VERSION_BTOOLS_SEEDIO})

target_link_libraries(btools-seedio
        -lboost_system
        -lboost_filesystem
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-seedio
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)