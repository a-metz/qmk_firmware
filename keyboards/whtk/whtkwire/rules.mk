# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
OLED_ENABLE = yes

DEFAULT_FOLDER = whtk/whtkwire
SRC +=  ../oled.c ../shift_alternative.c ../state.c