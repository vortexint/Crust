#![no_std]
#![no_main]

use core::panic::PanicInfo;

extern "C" {
    fn c_main();
}

/* Entry point function */
#[no_mangle]
pub extern "C" fn os_main() -> ! {
    unsafe {
        c_main();
    }
    loop {
    }
}


/* Panic Handler function */
#[no_mangle] #[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop{}
}