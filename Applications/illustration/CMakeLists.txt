cmake_minimum_required(VERSION 3.2)
project(btools-illustration)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(illustration
        illustration.cpp
        src/AroundBoundaryReasoning.cpp
        src/ElasticaProblem/model/ElasticaInput.cpp
        src/ElasticaProblem/model/Inbox.cpp
        src/ElasticaProblem/ElasticaProblem.cpp)

target_compile_definitions(illustration PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_include_directories(illustration PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(illustration
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lscabolic-core
        -lscabolic-energy
        -lscabolic-optimization
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})