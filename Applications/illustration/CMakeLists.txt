cmake_minimum_required(VERSION 3.2)
project(btools-illustration)

find_package(DGtal REQUIRED)

add_executable(illustration
        illustration.cpp
        src/AroundBoundaryReasoning.cpp)

target_compile_definitions(illustration PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_include_directories(illustration PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(illustration
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES})