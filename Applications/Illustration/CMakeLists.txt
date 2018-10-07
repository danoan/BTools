cmake_minimum_required(VERSION 3.2)
project(btools-illustration)

link_directories(ext/lib)


find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(illustration
        illustration.cpp
        src/AroundBoundaryReasoning.cpp
        src/Flow.cpp
        src/OneImageFlow.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/strUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/imgUtils.cpp
        )

target_compile_definitions(illustration PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(illustration PRIVATE cxx_auto_type)
target_compile_options(illustration PRIVATE -fext-numeric-literals)

target_include_directories(illustration PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${CMAKE_SOURCE_DIR}/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(illustration
        -lbinocs-application
        -lscabolic-energy
        -lscabolic-core
        -lscabolic-optimization
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})