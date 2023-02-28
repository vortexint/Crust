# This is a cmake toolchain variables file, it is not related to Rust's x86_64.json file. 
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_ASM_COMPILER "/usr/bin/nasm")
set(CMAKE_C_COMPILER   "/usr/bin/gcc")
set(CMAKE_LINKER       "/usr/bin/ld")

set(CMAKE_C_FLAGS "-m64 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore" CACHE INTERNAL "")
set(CMAKE_ASM_NASM_FLAGS "-f elf64" CACHE INTERNAL "")
#set(CMAKE_EXE_LINKER_FLAGS )

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)