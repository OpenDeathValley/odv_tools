set(INCROOT ${CMAKE_SOURCE_DIR}/src/core)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/core)

set(SRC ${SRCROOT}/ODVFile.c)

add_library(core ${SRC})