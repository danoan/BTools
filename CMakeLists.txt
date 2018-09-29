cmake_minimum_required(VERSION 3.2)
project(binocs-experiments)


#It expects variables
#CMAKE_PREFIX_PATH: find_[package] macro directories
#CMAKE_INSTALL_PREFIX: install location
#EXTRA_LINK_DIR: extra link directories
#BUILD_PATH: location of cmake generated build files


link_directories(${EXTRA_LINK_DIR})


find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

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
        ext/include
        include
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

target_include_directories(testWriting PRIVATE
        ext/include
        include
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

