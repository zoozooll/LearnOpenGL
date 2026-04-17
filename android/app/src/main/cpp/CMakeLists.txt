cmake_minimum_required(VERSION 3.22.1)

project("learnopengl")

find_library(
    log-lib
    log
)

find_library(
    glesv2-lib
    GLESv2
)

add_library(
    learnopengl
    SHARED
    native-lib.cpp
)

target_link_libraries(
    learnopengl
    ${log-lib}
    ${glesv2-lib}
)