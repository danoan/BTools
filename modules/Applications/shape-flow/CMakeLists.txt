cmake_minimum_required(VERSION 3.2)
project(shape-flow)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(shape-flow
        shape-flow.cpp
        src/control/DataWriter.cpp
        src/control/FlowControl.cpp
        src/model/InputReader.cpp
        )

add_dependencies(shape-flow btools-core btools-utils btools-visitors)

target_compile_features(shape-flow PRIVATE cxx_auto_type)
target_compile_options(shape-flow PRIVATE -fext-numeric-literals)

target_include_directories(shape-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(shape-flow
        -lbtools-utils
        -lbtools-core
        -lscabolic-utils
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

install(TARGETS shape-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
