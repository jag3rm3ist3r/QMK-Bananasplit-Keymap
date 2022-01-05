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
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	# USB Nkey Rollover - not yet supported in LUFA
BACKLIGHT_ENABLE = yes
#TERMINAL_ENABLE = yes	# Enable keyboard terminal (on/off == TERM_ON/TERM_OFF)
KEY_LOCK_ENABLE = yes	# Enable KC_LOCK keycode for simulating held keys.
#COMBO_ENABLE = yes # Enable combo sequences to trigger macros and keypresses.
COMBO_ALLOW_ACTION_KEYS = yes # Enable combo sequences to trigger from action keys as well as basic keycodes.
TAP_DANCE_ENABLE = yes # Enable double tap functions.
LEADER_ENABLE = yes # Enable leader key KC_LEAD to be used to create lead sequences.

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

LAYOUTS = 60_ansi 60_iso


