cmake_minimum_required(VERSION 3.22.1)

project("hello_window")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

set(LEARN_OPENGL_ROOT_FOLDER "../../../../../..")
set(LEARN_OPENGL_TITLE "1.getting_started")
set(LEARN_OPENGL_TUTORIAL "1.1.hello_window")
set(LEARN_OPENGL_PROJECT_FOLDER ${LEARN_OPENGL_ROOT_FOLDER}/src/${LEARN_OPENGL_TITLE}/${gggggggggggggggggggggggggggggggggggggggggg})

include_directories(
    ${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        ${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library(hello_window SHARED native-lib.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
)

target_link_libraries(hello_window ${log-lib} ${glesv3-lib})
