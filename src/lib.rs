#![no_std]
#![no_main]

use core::panic::PanicInfo;
// use core::arch::asm;

//static HELLO: &[u8] = b"Hello World!";

/* Entry point function */
#[no_mangle]
pub extern "C" fn _start() -> ! {
    loop {}
}


/* Panic Handler function */
#[no_mangle] #[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop{}
}