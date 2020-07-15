cmake_minimum_required(VERSION 3.2)
project(boundary-correction-app)

add_executable(boundary-correction-app boundary-correction.cpp
        src/InputReader.cpp)

add_dependencies(boundary-correction-app btools-api btools-seedio btools-core btools-utils)

target_compile_features(boundary-correction-app PRIVATE cxx_auto_type)
target_compile_options(boundary-correction-app PRIVATE -fext-numeric-literals)

target_include_directories(boundary-correction-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(boundary-correction-app
        -lbtools-api
        -lbtools-seedio
        -lbtools-core
        -lbtools-utils
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

install(TARGETS boundary-correction-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

