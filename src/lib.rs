#![no_std]
#![no_main]

use core::panic::PanicInfo;
// use core::arch::asm;

static MESSAGE: &[u8] = b"Welcome to Vortex OS!";

/* Entry point function */
#[no_mangle]
pub extern "C" fn os_main() -> ! {
    let vga_buffer = 0xb8000 as *mut u8;

    for (i, &byte) in MESSAGE.iter().enumerate() {
        unsafe {
            if i < 11 {
                *vga_buffer.offset(i as isize * 2) = byte;
                *vga_buffer.offset(i as isize * 2 + 1) = 0xf;
            } else {
                *vga_buffer.offset(i as isize * 2) = byte;
                *vga_buffer.offset(i as isize * 2 + 1) = 0x2;
            }
        }
    }

    loop {}
}


/* Panic Handler function */
#[no_mangle] #[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop{}
}