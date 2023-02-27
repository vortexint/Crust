#![no_std]
#![no_main]

use core::panic::PanicInfo;
// use core::arch::asm;

extern "C" {
    fn nnum(num: i32);
}

/* Entry point function */
#[no_mangle]
pub extern "C" fn os_main() -> ! {
    unsafe { 
        nnum(50)
    }

    loop {
    }
}


/* Panic Handler function */
#[no_mangle] #[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop{}
}