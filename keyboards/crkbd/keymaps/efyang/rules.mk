OLED_DRIVER_ENABLE = yes
WPM_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGB_UNDERGLOW_ENABLE = yes

ifdef OLED_DRIVER_ENABLE
  # Include my fancy rgb functions source here
  SRC += bongo_animation.c
endif

MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = no
STENO_ENABLE = no
BOOTMAGIC_ENABLE =no
TERMINAL_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_LOCK_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
VELOCIKEY_ENABLE = no

LTO_ENABLE = yes
