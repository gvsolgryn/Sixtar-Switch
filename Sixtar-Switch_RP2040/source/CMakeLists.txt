cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Sixtar_Controller C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(Sixtar_Controller
main.c
)

pico_enable_stdio_usb(Sixtar_Controller 1)

pico_add_extra_outputs(Sixtar_Controller)

target_link_libraries(Sixtar_Controller pico_stdlib)