include(ExternalProject)

set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext-projects/source)
set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build)

include(ext-projects/cmake-files/DIPaCUS.cmake)
include(ext-projects/cmake-files/SCaBOliC.cmake)
include(ext-projects/cmake-files/GEOC.cmake)
include(ext-projects/cmake-files/GCurve.cmake)