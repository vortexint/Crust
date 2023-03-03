cmake_minimum_required(VERSION 3.15)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(vortexOS LANGUAGES C ASM_NASM)

set(src ${CMAKE_SOURCE_DIR}/src)

include_directories(PUBLIC
    ${CMAKE_SOURCE_DIR}/extern
    ${src}/std
)

# Create object files for custom linking step 
add_library(c_objs OBJECT) # force GCC to use -c which ignores linking step. 
add_library(asm_objs OBJECT)

target_sources(c_objs PUBLIC
# C (gcc)
    ${src}/main.c
    ${src}/graphics/vga_text.c
    ${src}/bda/bda_utils.c
)

target_sources(asm_objs PUBLIC
# Assembly (nasm)
    ${src}/platform/x86_64/boot.asm
    ${src}/platform/x86_64/long-mode-init.asm
    ${src}/platform/x86_64/multiboot-header.asm
)

target_compile_options(c_objs PRIVATE -m64 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore)
target_compile_options(asm_objs PRIVATE -f elf64)

#add_library(VortexOS $<TARGET_OBJECTS:c_objs> $<TARGET_OBJECTS:asm_objs>)
# I Wish! We cannot specify build flags for ld here so a custom build step is required.

add_custom_target(VortexOS ALL
    COMMAND cargo build
    COMMAND ld -n --gc-sections -T ${src}/platform/x86_64/link.ld -o ${CMAKE_BINARY_DIR}/VortexOS.bin $<TARGET_OBJECTS:c_objs> $<TARGET_OBJECTS:asm_objs> ${CMAKE_BINARY_DIR}/x86_64/debug/libvortex_os_rust.a
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/isofiles/boot/grub
    COMMAND cp ${CMAKE_BINARY_DIR}/VortexOS.bin ${CMAKE_BINARY_DIR}/isofiles/boot/VortexOS.bin
    COMMAND cp -a ${src}/platform/grub/. ${CMAKE_BINARY_DIR}/isofiles/boot/grub
    COMMAND grub-mkrescue --output=${CMAKE_BINARY_DIR}/VortexOS_x86_64.iso ${CMAKE_BINARY_DIR}/isofiles
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/isofiles/
    COMMAND rm -f ${CMAKE_BINARY_DIR}/VortexOS.bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS c_objs asm_objs
    BYPRODUCTS ${CMAKE_BINARY_DIR}/VortexOS_x86_64.iso
    COMMENT "Full VortexOS kernel target"
    COMMAND_EXPAND_LISTS
    VERBATIM
)