ExternalProject_Add(magLac
        GIT_REPOSITORY https://github.com/danoan/magLac.git
        GIT_TAG master
        SOURCE_DIR ${EXTPROJECTS_SOURCE_DIR}/magLac
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${EXTPROJECTS_BUILD_DIR}
        -DBOOST_LIBS_DIR=${BOOST_LIBS_DIR}
        -DBOOST_INCLUDE_DIRS=${BOOST_INCLUDE_DIRS})