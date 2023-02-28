cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/x86_64.cmake)

project(vortex_os LANGUAGES C ASM_NASM)

set(src ${CMAKE_SOURCE_DIR}/src)

add_library(vortex_os STATIC)

target_include_directories(vortex_os PUBLIC
    ${CMAKE_SOURCE_DIR}/extern
)

target_sources(vortex_os PUBLIC
# Assembly
    ${src}/platform/x86_64/boot.asm
    ${src}/platform/x86_64/long-mode-init.asm
    ${src}/platform/x86_64/multiboot-header.asm
# C
    ${src}/main.c
    ${src}/graphics/vga_text.c
)