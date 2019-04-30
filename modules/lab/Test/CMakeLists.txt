cmake_minimum_required(VERSION 3.2)
project(btools-test)

add_executable(testWriting
        testWriting.cpp)

target_compile_definitions(testWriting PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(testWriting PRIVATE cxx_auto_type)
target_compile_options(testWriting PRIVATE -fext-numeric-literals)

target_include_directories(testWriting  PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BINOCS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(testWriting
        -lbinocs-utils
        -lbinocs-application
        -ldipacus-components
        -ldipacus-base
        -lscabolic-core
        -lscabolic-energy
        -lscabolic-optimization
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
