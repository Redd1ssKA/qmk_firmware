#ifndef QMK_INTELLISENSE_SHIM_H
#define QMK_INTELLISENSE_SHIM_H

#include <stdint.h>
#include <stdbool.h>

// Minimal shim for IntelliSense only. Not used in real builds.
#ifndef __INTELLISENSE__
#error "This shim is for IntelliSense only"
#endif

#ifndef SAFE_RANGE
#define SAFE_RANGE 0x1000
#endif

typedef uint16_t keycode_t;
typedef uint16_t uint16_t_shim;

typedef struct {
    struct { bool pressed; } event;
} keyrecord_t;

// common types
typedef uint16_t keypos_t;

// minimal keycodes used in keymap.c (expand if needed)
#define KC_ESC 0x29
#define KC_1 0x1E
#define KC_2 0x1F
#define KC_3 0x20
#define KC_4 0x21
#define KC_5 0x22
#define KC_6 0x23
#define KC_7 0x24
#define KC_8 0x25
#define KC_9 0x26
#define KC_0 0x27

#define KC_BSPC 0x2A
#define KC_TAB 0x2B
// Modifier and common keys (values are placeholders for IntelliSense only)
#define KC_LSFT 0xE1
#define KC_LCTL 0xE0
#define KC_LGUI 0xE3
#define KC_LALT 0xE2
#define KC_RSFT 0xE4
#define KC_ENT 0x28
#define KC_SPC 0x2C

// Alphabet keys (USB HID usage IDs)
#define KC_A 0x04
#define KC_B 0x05
#define KC_C 0x06
#define KC_D 0x07
#define KC_E 0x08
#define KC_F 0x09
#define KC_G 0x0A
#define KC_H 0x0B
#define KC_I 0x0C
#define KC_J 0x0D
#define KC_K 0x0E
#define KC_L 0x0F
#define KC_M 0x10
#define KC_N 0x11
#define KC_O 0x12
#define KC_P 0x13
#define KC_Q 0x14
#define KC_R 0x15
#define KC_S 0x16
#define KC_T 0x17
#define KC_U 0x18
#define KC_V 0x19
#define KC_W 0x1A
#define KC_X 0x1B
#define KC_Y 0x1C
#define KC_Z 0x1D

#define KC_VOLU 0x80
#define KC_VOLD 0x81
#define KC_MUTE 0x7F
#define KC_PGDN 0x4E
#define KC_PGUP 0x4B

#define KC_P7 0x5F
#define KC_P8 0x60
#define KC_P9 0x61
#define KC_P1 0x59
#define KC_P2 0x5A
#define KC_P3 0x5B
#define KC_P4 0x5C
#define KC_P5 0x5D
#define KC_P6 0x5E
#define KC_P0 0x62
#define KC_PSLS 0x54
#define KC_PAST 0x55
#define KC_PPLS 0x57

#define KC_NO 0x00

// basic helpers used by keymap.c
static inline void tap_code(uint16_t kc) { (void)kc; }
static inline void register_code(uint16_t kc) { (void)kc; }
static inline void unregister_code(uint16_t kc) { (void)kc; }
static inline void layer_on(int l) { (void)l; }
static inline void layer_off(int l) { (void)l; }

// Minimal matrix/layout helpers for IntelliSense parsing
#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef MATRIX_ROWS
#define MATRIX_ROWS 6
#endif

#ifndef MATRIX_COLS
#define MATRIX_COLS 10
#endif

#ifndef LAYOUT
#define LAYOUT(...) { __VA_ARGS__ }
#endif

#endif // QMK_INTELLISENSE_SHIM_H
