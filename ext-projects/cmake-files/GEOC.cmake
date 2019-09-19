ExternalProject_Add(geoc
        GIT_REPOSITORY https://github.com/danoan/GEOC.git
        GIT_TAG master
        SOURCE_DIR ${EXTPROJECTS_SOURCE_DIR}/GEOC
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${EXTPROJECTS_BUILD_DIR}
        -DUSE_REMOTE_REPOSITORIES=OFF
        -DDIPACUS_INCLUDE_DIRS=${EXTPROJECTS_BUILD_DIR}/include
        -DDIPACUS_LIBS_DIR=${EXTPROJECTS_BUILD_DIR}/lib)

add_dependencies(geoc dipacus)