cmake_minimum_required(VERSION 3.2)
project(seed-selector)

add_executable(seed-selector seed-selector.cpp
        src/GUIControl.cpp
        src/GUIData.cpp
        src/InputData.cpp
        src/MaskSelector.cpp
        src/RectSelector.cpp)

target_include_directories(seed-selector PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(seed-selector
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS seed-selector
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)