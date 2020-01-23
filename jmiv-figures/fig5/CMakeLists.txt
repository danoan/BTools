cmake_minimum_required(VERSION 3.2)
project(jmiv-fig5)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(jmiv-fig5 jmiv-fig5.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(jmiv-fig5 dipacus)
endif()


target_link_directories(jmiv-fig5 PRIVATE
        ${DIPACUS_LIBS_DIR}
        ${CMAKE_PREFIX_PATH}
        ${BOOST_LIBS_DIR})

target_include_directories(jmiv-fig5 PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(jmiv-fig5
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lscabolic-core
        -lscabolic-energy
        -lscabolic-optimization
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS jmiv-fig5
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
