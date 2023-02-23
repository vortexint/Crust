# My sincere apologies to anyone reading this Makefile
# Packages: rust, qemu, nasm, mtools, xorriso...

arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/vortex-os-$(arch).iso

linker_script := src/$(arch)/link.ld
grub_cfg := src/$(arch)/grub.cfg
asm_src := $(wildcard src/$(arch)/*.asm)
asm_obj := $(patsubst src/$(arch)/%.asm, \
	build/$(arch)/obj/%.o, $(asm_src))

.PHONY: all clean run iso kernel

all: $(kernel)

clean:
	@rm -r build || true
	@cargo clean

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)


iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp build/kernel.bin build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue --output=$(iso) build/isofiles

kernel:
# Compile rust source
	@cargo build
	@mkdir -p build/$(arch)/obj
# Compile assembly
	@for file in src/$(arch)/*.asm; do \
		nasm -f elf64 $$file -o build/$(arch)/obj/`basename $$file .asm`.o; \
	done


$(kernel): kernel $(asm_obj)
# link, create kernel.bin
	@ld -n --gc-sections -T src/$(arch)/link.ld -o build/kernel.bin \
		$(asm_obj) target/buildspec/debug/libvortex_os.a