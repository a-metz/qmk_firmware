# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
OLED_ENABLE = no
SERIAL_DRIVER = usart
DEBOUNCE_TYPE = sym_eager_pk

DEFAULT_FOLDER = whtk/whtkwire_split
SRC +=  ../oled.c ../shift_alternative.c ../state.c