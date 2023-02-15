# MCU name
MCU = atmega32u4

# Bootloader selection
#BOOTLOADER = atmel-dfu
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = no #yes # Mouse keys
EXTRAKEY_ENABLE  = no      # Audio control and System control
#CONSOLE_ENABLE   = yes #no       # Console for debug
CONSOLE_ENABLE   = no       # Console for debug
COMMAND_ENABLE   = no       # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE      = no #yes       # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE      = no
UNICODE_ENABLE   = no
UNICODEMAP_ENABLE = no
UCIS_ENABLE      = no
RGBLIGHT_ENABLE  = no       # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE     = no       # Audio output
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no

# https://docs.qmk.fm/#/feature_joystick
#JOYSTICK_ENABLE = analog
JOYSTICK_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = analog_joystick
SRC             += analog.c

#LTO_ENABLE = yes
