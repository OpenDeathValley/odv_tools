set(INCROOT ${CMAKE_SOURCE_DIR}/src/core)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/core)

set(SRC

	${SRCROOT}/odv_file_stream.h

)

if (WIN32)
  set(SRC
    ${SRC}
    ${SRCROOT}/win_odv_file_stream.c
    )
else ()
  set(SRC
    ${SRC}
    ${SRCROOT}/unix_odv_file_stream.c
    )
endif ()

add_library(core ${SRC})