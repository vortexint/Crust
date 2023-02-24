# Vortex OS

A memory-safe operating system built to maximize the potential of modern computing. Taking advantage of the Rust programming language and its associated ecosystem, Vortex OS is designed to be flexible and customizable from the ground up.

The project is implemented as a library, which can be linked with assembly source to produce a final kernel binary. The binary is then packed with the [GRUB 2 bootloader](https://www.gnu.org/software/grub/), allowing Vortex OS to be compatible with multiple boot environments; This design choice allows for flexibility and customization in the development process.

# Rundown

## 1. Hacking Rust

At the heart of Vortex OS lies a unique approach to using multiple languages in combination with Rust. To make the most out of the language, Vortex OS requires the use of the nightly version of Rust.

### 1.1 The x86_64-unknown-none LLVM target

In the development of kernels and other low-level software, extra attention is needed when using registers. To prevent any potential conflicts, the `x86_64-unknown-none` target is defaulted to not enable any vector or floating-point registers. However, these can still be used with care. By utilizing the `target-feature` technique, full programs or individual functions can be given access to such registers.

### 1.2 Disabling the Standard Library
Since no useable code has been loaded prior to the kernel in a bare metal environment, the OS, along with the crates it uses, can only rely on the hardware to run. To prevent Rust from loading the standard library, the `#[no_std]` crate-level attribute is used, which indicates that the crate will link to the `core-crate` instead of the `std-crate`. This will exclude components that may not be beneficial in embedded environments, such as a memory allocator for dynamic memory allocation.

### 1.3 Compiling the Kernel as a static library
When compiling the kernel as a static library, we still need some form of identifying which function is the entry point, so the rest of the source can be executed in sequence. To do this, we must avoid avoid a certain Rust feature called [Name mangling](https://en.wikipedia.org/wiki/Name_mangling) which modifies the names of functions to some incomprehensible gibberish. Thankfully, the `#[no_mangle]` attribute is used to define native functions such as the entry point `os_main()`, allowing them to be added as external functions in our assembly initialization source. 

> From the compiler perspective, it doesn't matter if the main function is in a static library or a standalone object file, the compiler can produce the kernel executable from object files regardless of their origin. 

### 1.4 The bootloader
By itself, the kernel is not capable of booting. A bootloader is necessary for the kernel to be able to boot. GRUB 2 is ideal for this purpose, and it can be configured to load the kernel image and set up a minimal environment for it to run. Additionally, many Linux distributions include GRUB 2 as their main bootloader, granting multiboot capabilities with different Operating Systems.