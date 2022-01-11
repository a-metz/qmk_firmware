# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP = yes

# Build Options
#   change yes to no to disable
#
EXTRAKEY_ENABLE = yes       # Audio control and System control
OLED_ENABLE = yes

DEBOUNCE_TYPE = sym_eager_pk
