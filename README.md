# Vortex OS

An operating system built with memory-safety in mind.

The project is implemented as a library, which can be linked with assembly source to produce a final kernel binary. The binary is then packed with the [GRUB 2 bootloader](https://www.gnu.org/software/grub/), allowing Vortex OS to be compatible with multiple boot environments; This design choice allows for flexibility and customization in the development process.

## 1. Hacking Rust

Some different methods are used in order to enable the usage
of multiple languages in combination with Rust. Nightly version is needed.

### 1.1 The x86_64-unknown-none LLVM target

Because kernels, modules, and similar software require extra attention when using such registers, the `x86_64-unknown-none` target will default to not enabling the usage of any vector or floating-point registers.
The Linux kernel, for example, normally optimizes kernel entry and exit by not saving and restoring such registers; kernel code must explicitly request the use of such registers before running code that uses them, and once requested, the kernel must pay the additional overhead of saving userspace registers to make way for the kernel usage.
When using the `x86_64-unknown-none` target, we can still use such registers by using the target-feature technique, either for a full program or for individual functions. 

### 1.2 Disabling the Standard Library
In a bare metal environment, no useable code has been loaded prior to the kernel. Without the software provided by an OS, the OS, along with the crates it uses, can only rely on the hardware to run. To prevent Rust from loading the standard library, the `no_std` crate-level attribute is used, it indicates that the crate will link to the `core-crate` instead of the `std-crate`.

The platform-agnostic parts of the standard library are available through libcore, which also excludes components that may not be beneficial in embedded environments. For example, libcore does not include a memory allocator for dynamic memory allocation. For such features, or any other functionalities, there are crates that can provide these.

### 1.3 Compiling the Kernel as a static library
From the compiler perspective, it doesn't matter if the main function is in a static library or a standalone object file, the compiler can produce the kernel executable from object files regardless of their origin. Once the kernel is linked (e.g: with assembly code for the multiboot header), all the distinctions between library and non-library symbols will be lost.

That said, we still need some form of identifying which function is the entry point, so the rest of the source can be executed in sequence; Normally, in a C development environment you'd be able to simple list the name of the function as an external C function in assembly code. However, in this scenario, Rust deploys a feature called [Name mangling](https://en.wikipedia.org/wiki/Name_mangling), to avoid scenarios where functions with identical names collide, this means that the names will be modified to some incomprehensible gibberish, this is why the `#[no_mangle]` attribute is used to define native functions such as the entry point `os_main()`, we can then proceed to add these as external functions in our assembly initialization source... 

### 1.4 The bootloader
By itself, the kernel is not capable of booting. For that, a bootloader is necessary. GRUB 2 is an ideal for this purpose. It can be configured to load the kernel image and set up a minimal environment for it to run. Additionally, many Linux distributions include GRUB 2 as their main bootloader, granting multiboot capabilities with different Operating Systems.