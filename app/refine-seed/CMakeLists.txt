cmake_minimum_required(VERSION 3.2)
project(refine-seed)

add_executable(refine-seed refine-seed.cpp
        src/GUIControl.cpp
        src/GUIData.cpp
        src/InputData.cpp
        src/MaskSelector.cpp
        src/RectSelector.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(refine-seed dipacus btools-utils)
else()
    add_dependencies(refine-seed btools-utils)
endif()


target_include_directories(refine-seed PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${BOOST_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(refine-seed
        -ldipacus-components
        -ldipacus-base
        -lbtools-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS refine-seed
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


