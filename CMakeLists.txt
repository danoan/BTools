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
        src/BinOCS/Experiments/utils.cpp
        src/BinOCS/Experiments/ExpInteractive.cpp
        src/BinOCS/Experiments/model/ExpDataInput.cpp
        src/BinOCS/Experiments/ROISelection.cpp)

target_include_directories(main PRIVATE
        ext/include
        include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(main
        -lbinocs-application
        -ldipacus-components
        -ldipacus-base
        -lscabolic-core
        -lscabolic-energy
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})