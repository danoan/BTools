cmake_minimum_required(VERSION 3.2)
project(levels-contribution)

add_executable(levels-contribution levels-contribution.cpp src/FlowControl.cpp src/InputReader.cpp)
add_dependencies(levels-contribution btools-utils btools-core btools-visitors)

target_include_directories(levels-contribution PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/visitors/include
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(levels-contribution
        -lbtools-utils
        -lbtools-core
        -lbtools-visitors
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

INSTALL(TARGETS levels-contribution
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)