cmake_minimum_required(VERSION 3.2)
project(export-seed-mask)

add_executable(export-seed-mask
        export-seed-mask.cpp)

add_dependencies(export-seed-mask btools-utils btools-seedio)

target_include_directories(export-seed-mask PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(export-seed-mask
        -lbtools-seedio
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${OpenCV_LIBS})

install(TARGETS export-seed-mask
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)