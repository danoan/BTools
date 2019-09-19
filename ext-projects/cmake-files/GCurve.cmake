ExternalProject_Add(gcurve
        GIT_REPOSITORY https://github.com/danoan/GCurve.git
        GIT_TAG master
        SOURCE_DIR ${EXTPROJECTS_SOURCE_DIR}/GCurve
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${EXTPROJECTS_BUILD_DIR}
        -DUSE_REMOTE_REPOSITORIES=OFF
        -DDIPACUS_INCLUDE_DIRS=${EXTPROJECTS_BUILD_DIR}/include
        -DDIPACUS_LIBS_DIR=${EXTPROJECTS_BUILD_DIR}/lib
        -DCREATE_SHARED_LIBRARIES=ON)

add_dependencies(gcurve dipacus)