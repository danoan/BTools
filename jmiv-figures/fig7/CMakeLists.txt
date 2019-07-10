cmake_minimum_required(VERSION 3.2)
project(jmiv-fig7)

add_executable(jmiv-fig7 jmiv-fig7.cpp)

if(${USE_LOCAL_REPOSITORIES})
    add_dependencies(jmiv-fig7 btools-core btools-reader btools-utils scabolic dipacus)
else()
    add_dependencies(jmiv-fig7 btools-core btools-reader btools-utils)
endif()


target_include_directories(jmiv-fig7 PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(jmiv-fig7
        -lbtools-core
        -lbtools-reader
        -lbtools-utils
        -lscabolic-optimization
        -lscabolic-energy
        -lscabolic-core
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS jmiv-fig7
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)