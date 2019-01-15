#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>

#define KEY_UNDEFINED 0x00

#define KEY_A 0x01
#define KEY_B 0x02
#define KEY_C 0x03
#define KEY_D 0x04
#define KEY_E 0x05
#define KEY_F 0x06
#define KEY_G 0x07
#define KEY_H 0x08
#define KEY_I 0x09
#define KEY_J 0x0A
#define KEY_K 0x0B
#define KEY_L 0x0C
#define KEY_M 0x0D
#define KEY_N 0x0E
#define KEY_O 0x0F
#define KEY_P 0x10
#define KEY_Q 0x11
#define KEY_R 0x12
#define KEY_S 0x13
#define KEY_T 0x14
#define KEY_U 0x15
#define KEY_V 0x16
#define KEY_W 0x17
#define KEY_X 0x18
#define KEY_Y 0x19
#define KEY_Z 0x1A

#define KEY_0 0x20
#define KEY_1 0x21
#define KEY_2 0x22
#define KEY_3 0x23
#define KEY_4 0x24
#define KEY_5 0x25
#define KEY_6 0x26
#define KEY_7 0x27
#define KEY_8 0x28
#define KEY_9 0x29

#define KEY_ESCAPE     0x30
#define KEY_SPACE      0x31
#define KEY_RETURN     0x32
#define KEY_BACKSPACE  0x33
#define KEY_AUP        0x34
#define KEY_ADOWN      0x35
#define KEY_ALEFT      0x36
#define KEY_ARIGHT     0x37
#define KEY_CAPS       0x38
#define KEY_TAB        0x39

#define KEY_MOD_SHIFT   0x8000
#define KEY_MOD_ALT     0x4000
#define KEY_MOD_CONTROL 0x2000

#define KEY_MAX 0xFFFF

typedef struct {
  int current_modifier;
  int keys[KEY_MAX];
} InputHandler;

extern void win32_input_down(InputHandler* input, WPARAM wParam, LPARAM lParam);
extern void win32_input_up(InputHandler* input, WPARAM wParam, LPARAM lParam);

extern int is_key_down(InputHandler* input, int keycode);
extern int is_key_mod_down(InputHandler* input, int keycode, int modifiers);


#endif
