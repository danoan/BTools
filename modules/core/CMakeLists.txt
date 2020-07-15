cmake_minimum_required(VERSION 3.2)
project(btools-core)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-core ${LIBRARY_ACTION}
        src/control/modelIteration.cpp
        src/model/GMM.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(btools-core dipacus scabolic btools-utils)
else()
    add_dependencies(btools-core btools-utils)
endif()

set_target_properties(btools-core PROPERTIES
        VERSION ${VERSION_BTOOLS_CORE})

target_include_directories(btools-core PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(btools-core
        -lbtools-utils
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