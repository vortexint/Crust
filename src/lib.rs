#![no_std]
#![no_main]

use core::panic::PanicInfo;

/* Entry point function */
#[no_mangle]
pub extern "C" fn os_main() -> ! {

    loop {
    }
}


/* Panic Handler function */
#[no_mangle] #[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop{}
}