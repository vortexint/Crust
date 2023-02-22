# Vortex OS

An operating system built with memory-safety in mind.

The project is implemented as a library, which can be linked with assembly source to produce a final kernel binary. The binary is then packed with the GRUB 2 bootloader, allowing Vortex OS to be compatible with multiple boot environments; This design choice allows for flexibility and customization in the development process.

## Hacking Rust

Some different methods are used in order to enable the usage
of multiple languages in combination with Rust. Nightly version is needed.

### The x86_64-unknown-none LLVM target

Because kernels, modules, and similar software require extra attention when using such registers, the `x86_64-unknown-none` target will default to not enabling the usage of any vector or floating-point registers.
The Linux kernel, for example, normally optimizes kernel entry and exit by not saving and restoring such registers; kernel code must explicitly request the use of such registers before running code that uses them, and once requested, the kernel must pay the additional overhead of saving userspace registers to make way for the kernel usage.
When using the `x86_64-unknown-none` target, we can still use such registers by using the target-feature technique, either for a full program or for individual functions. 

### Disabling the Standard Library
In a bare metal environment, no useable code has been loaded prior to the kernel. Without the software provided by an OS, the OS, along with the crates it uses, can only rely on the hardware to run. To prevent Rust from loading the standard library, the `no_std` attribute is used.

The platform-agnostic parts of the standard library are available through libcore, which also excludes components that may not be beneficial in embedded environments. For example, libcore does not include a memory allocator for dynamic memory allocation. For such features, or any other functionalities, there are often crates that provide these.