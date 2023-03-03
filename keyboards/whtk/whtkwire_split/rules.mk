# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
# OLED_ENABLE = yes
SERIAL_DRIVER = usart
DEBOUNCE_TYPE = sym_eager_pk
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = yes

DEFAULT_FOLDER = whtk/whtkwire_split
SRC +=  ../oled.c ../shift_alternative.c ../state.c