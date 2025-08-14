#pragma once

// #define MATRIX_ROWS 3
// #define MATRIX_COLS 3

// #define MATRIX_COL_PINS { GP2, GP3, GP4 }
// #define MATRIX_ROW_PINS { GP6, GP7, GP8 }

// #define DIODE_DIRECTION COL2ROW

// #define USB_VID 0xCafe
// #define USB_PID 0x6001
// #define MANUFACTURER "Carlos Mondragon"
// #define PRODUCT "Tami9"
// #define DEVICE_VER 0x0001

// LAYER
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// CRYSTAL SETTING
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader
