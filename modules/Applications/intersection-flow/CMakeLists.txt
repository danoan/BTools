cmake_minimum_required(VERSION 3.2)
project(intersection-flow)

add_executable(intersection-flow intersection-flow.cpp)
add_dependencies(shape-flow btools-core btools-utils)

target_include_directories(intersection-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(intersection-flow
        -lbtools-core
        -lbtools-utils
        -ldipacus-derivates
        -ldipacus-base
        -lscabolic-energy
        -lscabolic-core
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS intersection-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)