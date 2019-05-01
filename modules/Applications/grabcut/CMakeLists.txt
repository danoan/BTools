cmake_minimum_required(VERSION 3.2)
project(grab-cut)

add_executable(grab-cut GrabCut.cpp src/InputData.cpp src/GrabCutApplication.cpp)
target_include_directories(grab-cut PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRECTORIES})

target_link_libraries(grab-cut
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS grab-cut
        DESTINATION ${CMAKE_INSTALL_PREFIX})