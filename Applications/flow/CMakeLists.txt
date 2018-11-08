cmake_minimum_required(VERSION 3.2)
project(btools-flow)

link_directories(ext/lib)


find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(flow
        flow.cpp
        src/Flow.cpp
        src/OneImageFlow.cpp
        src/InputReader.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/strUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/imgUtils.cpp
        )

target_compile_definitions(flow PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(flow PRIVATE cxx_auto_type)
target_compile_options(flow PRIVATE -fext-numeric-literals)

target_include_directories(flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${CMAKE_SOURCE_DIR}/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(flow
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


add_executable(make-summary-flow
        makeSummaryFlow.cpp
        src/OneImageFlow.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/strUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/BTools/utils/imgUtils.cpp
        )

target_compile_definitions(make-summary-flow PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(make-summary-flow PRIVATE cxx_auto_type)
target_compile_options(make-summary-flow PRIVATE -fext-numeric-literals)

target_include_directories(make-summary-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${CMAKE_SOURCE_DIR}/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(make-summary-flow
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})