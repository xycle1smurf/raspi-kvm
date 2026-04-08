cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(rp2350_hid_uart C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(rp2350_hid_uart
    src/main.c
    src/usb_descriptors.c
    src/uart_protocol.c
)

target_include_directories(rp2350_hid_uart PRIVATE include)

target_link_libraries(rp2350_hid_uart
    pico_stdlib
    pico_stdio_uart
    hardware_uart
    tinyusb_device
    tinyusb_board
)

pico_enable_stdio_usb(rp2350_hid_uart 0)
pico_enable_stdio_uart(rp2350_hid_uart 0)

pico_add_extra_outputs(rp2350_hid_uart)
