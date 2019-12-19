cmake_minimum_required(VERSION 3.2)
project(jmiv-fig6)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(jmiv-fig6 jmiv-fig5.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(jmiv-fig6 dipacus)
endif()


target_link_directories(jmiv-fig6 PRIVATE
        ${DIPACUS_LIBS_DIR}
        ${CMAKE_PREFIX_PATH}
        ${BOOST_LIBS_DIR})

target_include_directories(jmiv-fig6 PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(jmiv-fig6
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES})

install(TARGETS jmiv-fig6
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)