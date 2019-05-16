cmake_minimum_required(VERSION 3.2)
project(btools-core)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-core ${LIBRARY_ACTION}
        src/BCApplication.cpp
        src/pool/ODRPool.cpp
        src/pool/FlowPool.cpp
        src/control/BCControl.cpp
        src/model/GMM.cpp
        src/model/SolutionHint.cpp)

target_include_directories(btools-core PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(btools-core
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lscabolic-core
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS}
        )

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-core
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)