# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
OLED_ENABLE = no
SERIAL_DRIVER = usart

DEFAULT_FOLDER = whtk/whtkbrd
SRC += ../shift_alternative.c ../state.c