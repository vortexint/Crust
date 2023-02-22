# Vortex OS

An operating system built with memory-safety in mind.

The project is implemented as a library, which can be linked with assembly source to produce a final kernel binary. The binary is then packed with the GRUB 2 bootloader, allowing Vortex OS to be compatible with multiple boot environments; This design choice allows for flexibility and customization in the development process.

## 1. Hacking Rust

Some different methods are used in order to enable the usage
of multiple languages in combination with Rust. Nightly version is needed.

### 1.1 The x86_64-unknown-none LLVM target

Because kernels, modules, and similar software require extra attention when using such registers, the `x86_64-unknown-none` target will default to not enabling the usage of any vector or floating-point registers.
The Linux kernel, for example, normally optimizes kernel entry and exit by not saving and restoring such registers; kernel code must explicitly request the use of such registers before running code that uses them, and once requested, the kernel must pay the additional overhead of saving userspace registers to make way for the kernel usage.
When using the `x86_64-unknown-none` target, we can still use such registers by using the target-feature technique, either for a full program or for individual functions. 

### 1.2 Disabling the Standard Library
In a bare metal environment, no useable code has been loaded prior to the kernel. Without the software provided by an OS, the OS, along with the crates it uses, can only rely on the hardware to run. To prevent Rust from loading the standard library, the `no_std` crate-level attribute is used, it indicates that the crate will link to the `core-crate` instead of the `std-crate`.

The platform-agnostic parts of the standard library are available through libcore, which also excludes components that may not be beneficial in embedded environments. For example, libcore does not include a memory allocator for dynamic memory allocation. For such features, or any other functionalities, there are crates that can provide these; Alternatively, they may be manually created.

### 1.3 Compiling the Kernel as a static library
 From the compiler perspective, it doesn't matter if the main function is in a static library or a standalone object file, the compiler can produce the kernel executable from object files regardless of their origin. Once the kernel is linked (e.g: with assembly code for the multiboot header), all the distinctions between library and non-library symbols will be lost.