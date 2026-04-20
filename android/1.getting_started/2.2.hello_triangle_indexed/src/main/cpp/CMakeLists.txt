cmake_minimum_required(VERSION 3.22.1)

project("hello_triangle_indexed")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

# If LEARN_OPENGL_ROOT_FOLDER is not passed from Gradle, use a relative path as fallback
if(NOT LEARN_OPENGL_ROOT_FOLDER)
    get_filename_component(LEARN_OPENGL_ROOT_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../.." ABSOLUTE)
endif()
set(LEARN_OPENGL_TITLE "1.getting_started")
set(LEARN_OPENGL_TUTORIAL "2.2.hello_triangle_indexed")
set(LEARN_OPENGL_PROJECT_FOLDER ${LEARN_OPENGL_ROOT_FOLDER}/src/${LEARN_OPENGL_TITLE}/${LEARN_OPENGL_TUTORIAL})

include_directories(
    ${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        ${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library(hello_triangle_indexed SHARED native-lib.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
    ${LEARN_OPENGL_ROOT_FOLDER}/src/stb_image.cpp
)

target_link_libraries(hello_triangle_indexed ${log-lib} ${glesv3-lib})
