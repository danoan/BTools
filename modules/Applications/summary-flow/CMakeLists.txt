cmake_minimum_required(VERSION 3.2)
project(summary-flow)

add_executable(summary-flow
        summary-flow.cpp
        src/OneImageFlow.cpp
        )

add_dependencies(shape-flow btools-core btools-utils)

target_compile_features(summary-flow PRIVATE cxx_auto_type)
target_compile_options(summary-flow PRIVATE -fext-numeric-literals)

target_include_directories(summary-flow PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        )

target_link_libraries(summary-flow
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lbtools-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS summary-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
