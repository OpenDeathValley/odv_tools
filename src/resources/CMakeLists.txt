set(INCROOT ${CMAKE_SOURCE_DIR}/src/resources)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/resources)

set(SRC ${SRCROOT}/ODVResourceManager.c)

add_library(resources ${SRC})