# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Select which side of the keyboard to build
SIDE = right

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
PRINT_ENABLE = no
DEBUG_ENABLE = no
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
DYNAMIC_MACRO_ENABLE = no
WPM_ENABLE = no
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

SPLIT_TRANSPORT = custom
QUANTUM_SRC += transport_custom.c
QUANTUM_LIB_SRC += serial.c


ifeq ($(strip $(SIDE)), left)
    # Enable display for left side
    OLED_DRIVER_ENABLE = yes
    SRC += bitmaps.c
    SRC += display.c
else ifeq ($(strip $(SIDE)), right)
    # Enable mouse for right side
    PS2_MOUSE_ENABLE = yes
    PS2_USE_INT = yes
#     PS2_USE_USART = yes
endif


