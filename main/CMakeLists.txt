file(GLOB_RECURSE SRC_UI
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.c"
)

idf_component_register(
    SRCS
        "main.c"
        "LCD.c"
        "giaodien.c"
        ${SRC_UI}
    INCLUDE_DIRS
        "."
        "ui"
)