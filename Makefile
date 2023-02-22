# My sincere apologies to anyone reading this Makefile
# Packages: rust, qemu, nasm, mtools, xorriso...

arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/vortex-os-$(arch).iso

grub_cfg := src/$(arch)/grub.cfg

.PHONY: all clean run iso kernel

all: $(kernel) iso

clean:
	@cargo clean
	@rm -r build || true

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)


iso: $(iso)

$(iso): $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp target/buildspec/debug/vortex_os build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue --output=$(iso) build/isofiles

kernel:
# Compile Rust source
	@cargo build
# Compile assembly
	@nasm -f elf64 multiboot_header.asm
# link it


$(kernel): kernel
