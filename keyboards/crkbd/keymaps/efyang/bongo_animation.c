#include QMK_KEYBOARD_H
#include "bongo_animation.h"

// WPM-responsive animation stuff here
#define IDLE_FRAMES 7
#define IDLE_SPEED 30 // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#define TAP_FRAMES 2
#define TAP_SPEED 50 // above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 22 // number of bytes in array, minimize for adequate firmware size, max is 1024


#define FRAME_SIZE 22
#define FRAME_WIDTH 32
#define FRAME_HEIGHT 31

#define HAT_FRAME_SIZE 22
#define HAT_FRAME_WIDTH 11
#define HAT_FRAME_HEIGHT 15

// 'tap-left', 32x31px
const char PROGMEM tap_left[FRAME_SIZE] = {
    0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0x24, 0x20, 0xa0, 0x20,
    0x10, 0x42, 0x40, 0x40, 0x00, 0x00
};

// 'tap-right', 32x31px
const char PROGMEM tap_right[FRAME_SIZE] = {
    0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0x24, 0x20, 0xa0, 0x20,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x00
};

const char* const PROGMEM tap_frames[TAP_FRAMES] = {
    tap_left,
    tap_right
};

const int tap_frame_hat_offset[TAP_FRAMES][2] = {
    {0, 0},
    {0, 0}
};

// 'tap-ready', 32x31px
const char PROGMEM ready[FRAME_SIZE] = {
    0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0x24, 0x20, 0xa0, 0x20,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x00
};

const int ready_frame_hat_offset[2] = {0, 0};

// 'idle1', 32x31px
const char PROGMEM idle1[FRAME_SIZE] = {
    0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0x24, 0x20, 0xa0, 0x20,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x00
};

// 'idle2', 32x31px
const char PROGMEM idle2[FRAME_SIZE] = {
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x08, 0x24, 0x00, 0x00, 0x00, 0x80,
    0x10, 0x00, 0x02, 0x00, 0x00, 0x00
};

// 'idle3', 32x31px
const char PROGMEM idle3[FRAME_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x92
};

// 'idle4', 32x31px
const char PROGMEM idle4[FRAME_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x10, 0x00, 0x02, 0x02, 0x12, 0x90
};

// 'idle5', 32x31px
const char PROGMEM idle5[FRAME_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x24, 0x20, 0x20, 0xa0, 0x20,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x02
};

// 'idle6', 32x31px
const char PROGMEM idle6[FRAME_SIZE] = {
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x08, 0x08, 0x24, 0x20, 0x20, 0xa0, 0x20,
    0x10, 0x02, 0x00, 0x00, 0x00, 0x00
};

const int idle_frame_hat_offset[IDLE_FRAMES][2] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

const char* const PROGMEM idle_frames[IDLE_FRAMES] = {
    idle1,
    idle2,
    idle3,
    idle4,
    idle5,
    idle6,
    idle1
};

// TODO: turn this into lines so write_ln can be used
// 'partyhat', 11x15px
const char PROGMEM partyhat[HAT_FRAME_SIZE] = {
    0x00, 0x00, 0x00, 0x80, 0x40, 0xa0, 0x14, 0x4b, 0xfe, 0x05, 0x0a, 0x0c, 0x12, 0x11, 0x24, 0x20,
    0x52, 0x54, 0x40, 0x7f, 0x40, 0x40
};

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;

// Images credit j-inc(/James Incandenza) and pixelbenny. Credit to obosob for initial animation approach.
void render_anim(void) {
    //assumes 1 frame prep stage
    void animation_phase(void) {
        if(get_current_wpm() <=IDLE_SPEED){
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle_frames[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
#ifdef BONGO_PARTY_HAT
#endif
        }

        if(get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED){
            oled_write_raw_P(ready, ANIM_SIZE);  // remove if IDLE_FRAMES >1
#ifdef BONGO_PARTY_HAT
#endif
        }

        if(get_current_wpm() >=TAP_SPEED){
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap_frames[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
#ifdef BONGO_PARTY_HAT
#endif
        }
    }

    if(get_current_wpm() != 0) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress

        if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }

        anim_sleep = timer_read32();
    } else {
        if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}
