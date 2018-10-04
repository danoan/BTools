cmake_minimum_required(VERSION 3.2)
project(binocs-experiments)


#CMAKE_INSTALL_PREFIX: install location

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(GEOC_INCLUDE_DIRS /usr/local/include/geoc CACHE PATH "geoc include location path.")

set(SCABOLIC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "SCaBOliC include location path.")
set(SCABOLIC_LIBS_DIR /usr/local/lib CACHE PATH "SCaBOliC libraries location path.")

set(BINOCS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "BinOCS include location path.")
set(BINOCS_LIBS_DIR /usr/local/lib CACHE PATH "BinOCS libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")


link_directories(${DIPACUS_LIBS_DIR}
        ${GEOC_LIBS_DIR}
        ${SCABOLIC_LIBS_DIR}
        ${BINOCS_LIBS_DIR}
        ${CMAKE_PREFIX_PATH})


add_executable(main
        src/main.cpp
        src/BinOCS/Lab/utils.cpp
        src/BinOCS/Lab/Experiments/model/SeedSequenceInput.cpp
        src/BinOCS/Lab/Experiments/ExpInteractive.cpp
        src/BinOCS/Lab/Experiments/ExpFromSeed.cpp
        src/BinOCS/Lab/Experiments/ExpDataset.cpp)



target_compile_definitions(main PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(main PRIVATE cxx_auto_type)
target_compile_options(main PRIVATE -fext-numeric-literals)

target_include_directories(main PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BINOCS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(main
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




add_executable(testWriting
        src/BinOCS/Lab/Test/testWriting.cpp
        src/BinOCS/Lab/utils.cpp)

target_compile_definitions(testWriting PRIVATE -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

target_compile_features(testWriting PRIVATE cxx_auto_type)
target_compile_options(testWriting PRIVATE -fext-numeric-literals)

target_include_directories(testWriting  PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${SCABOLIC_INCLUDE_DIRS}
        ${BINOCS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(testWriting
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

