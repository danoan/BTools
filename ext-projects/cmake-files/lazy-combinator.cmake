ExternalProject_Add(lazy-combinator
        GIT_REPOSITORY https://github.com/danoan/lazy-combinator.git
        GIT_TAG jmiv
        SOURCE_DIR ${EXTPROJECTS_SOURCE_DIR}/lazy-combinator
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_BUILD_TYPE=RELEASE
        -DCMAKE_INSTALL_PREFIX=${EXTPROJECTS_BUILD_DIR}
        -DBOOST_INCLUDE_DIRS=${BOOST_INCLUDE_DIRS})