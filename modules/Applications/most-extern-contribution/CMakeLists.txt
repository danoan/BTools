cmake_minimum_required(VERSION 3.2)
project(most-extern-contribution)

add_executable(most-extern-contribution most-extern-contribution.cpp src/FlowControl.cpp src/InputReader.cpp)

target_include_directories(most-extern-contribution PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${SCABOLIC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(most-extern-contribution
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lscabolic-core
        -lscabolic-energy
        -lscabolic-optimization
        -lbtools-core
        -lbtools-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

INSTALL(TARGETS most-extern-contribution
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)