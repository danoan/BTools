cmake_minimum_required(VERSION 3.2)
project(btools-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(btools-utils ${LIBRARY_ACTION}
        src/imgUtils.cpp
        src/strUtils.cpp
        src/timer.cpp
        src/digUtils.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(btools-utils dipacus)
endif()

set_target_properties(btools-utils  PROPERTIES
        VERSION ${VERSION_BTOOLS_UTILS})

target_include_directories(btools-utils PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(btools-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS btools-utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)