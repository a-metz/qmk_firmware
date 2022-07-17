# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
OLED_ENABLE = no
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

DEFAULT_FOLDER = whtk/whtkbrd
SRC +=  ../oled.c ../shift_alternative.c ../state.c