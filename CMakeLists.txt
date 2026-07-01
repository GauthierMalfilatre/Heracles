cmake_minimum_required(VERSION 3.5)
project(heracles LANGUAGES C)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "Les builds dans le dossier source sont interdits. Créez un dossier build/.")
endif()

file(GLOB_RECURSE heracles_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/heracles/src/*.c"
)

add_library(heracles-obj ${heracles_SOURCES})

target_include_directories(heracles-obj
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/heracles/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(heracles-obj PRIVATE
    -Wall
    -Wextra
    -O3
)

add_library(heracles-static STATIC
    $<TARGET_OBJECTS:heracles-obj>
)

target_link_libraries(heracles-static
    PUBLIC
        heracles-obj
)

add_library(heracles-shared SHARED
    $<TARGET_OBJECTS:heracles-obj>
)

target_link_libraries(heracles-shared
    PUBLIC
        heracles-obj
)

add_library(heracles ALIAS heracles-static)

set_target_properties(heracles-static PROPERTIES
    OUTPUT_NAME heracles
)

set_target_properties(heracles-shared PROPERTIES
    OUTPUT_NAME heracles
)

set_target_properties(heracles-obj PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
