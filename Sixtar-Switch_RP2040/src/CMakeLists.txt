cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Sixtar_Controller C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(Sixtar_Controller)

target_sources(Sixtar_Controller PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/include/usb_descriptors.c
)

target_include_directories(Sixtar_Controller PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

pico_add_extra_outputs(Sixtar_Controller)

target_link_libraries(Sixtar_Controller PUBLIC pico_stdlib tinyusb_device tinyusb_board)