cmake_minimum_required(VERSION 3.0.0)

project(vortex_os)
enable_language(C ASM_NASM)

set(CMAKE_SYSTEM_NAME VortexOS)
set(CMAKE_SYSTEM_VERSION 1)

set(src ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_C_FLAGS "-m64 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore")
set(CMAKE_ASM_NASM_FLAGS "-f elf64" )
set(CMAKE_LD_FLAGS "-n --gc-sections -T ${src}/platform/x86_64/link.ld -o ${CMAKE_BINARY_DIR}/kernel.bin ${CMAKE_BINARY_DIR}/libvortex_os.a ${CMAKE_BINARY_DIR}/x86_64/debug/libvortex_os_rust.a")

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

# Compile Rust

add_custom_command(TARGET vortex_os POST_BUILD
    COMMAND cargo build
    COMMAND ld ${CMAKE_LD_FLAGS}
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/isofiles/boot/grub
    COMMAND cp ${CMAKE_BINARY_DIR}/kernel.bin ${CMAKE_BINARY_DIR}/isofiles/boot/kernel.bin
    COMMAND cp -a ${src}/platform/grub/. ${CMAKE_BINARY_DIR}/isofiles/boot/grub
    COMMAND grub-mkrescue --output=${CMAKE_BINARY_DIR}/vortex-os-x86-64.iso ${CMAKE_BINARY_DIR}/isofiles
)

message(STATUS LDFLAGS IS: ${CMAKE_LD_FLAGS})