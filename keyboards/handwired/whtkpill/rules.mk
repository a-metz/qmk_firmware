# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
OLED_ENABLE = yes

DEBOUNCE_TYPE = sym_eager_pk

SRC += shift_alternative.c