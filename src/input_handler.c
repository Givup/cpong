#include "input_handler.h"

int winkey_to_keycode(WPARAM param) {
  switch(param) {

  // Alphabet
  case 0x41: return KEY_A;
  case 0x42: return KEY_B;
  case 0x43: return KEY_C;
  case 0x44: return KEY_D;
  case 0x45: return KEY_E;
  case 0x46: return KEY_F;
  case 0x47: return KEY_G;
  case 0x48: return KEY_H;
  case 0x49: return KEY_I;
  case 0x4A: return KEY_J;
  case 0x4B: return KEY_K;
  case 0x4C: return KEY_L;
  case 0x4D: return KEY_M;
  case 0x4E: return KEY_N;
  case 0x4F: return KEY_O;
  case 0x50: return KEY_P;
  case 0x51: return KEY_Q;
  case 0x52: return KEY_R;
  case 0x53: return KEY_S;
  case 0x54: return KEY_T;
  case 0x55: return KEY_U;
  case 0x56: return KEY_V;
  case 0x57: return KEY_W;
  case 0x58: return KEY_X;
  case 0x59: return KEY_Y;
  case 0x5A: return KEY_Z;
  
  // Numbers
  case 0x30: return KEY_0;
  case 0x31: return KEY_1;
  case 0x32: return KEY_2;
  case 0x33: return KEY_3;
  case 0x34: return KEY_4;
  case 0x35: return KEY_5;
  case 0x36: return KEY_6;
  case 0x37: return KEY_7;
  case 0x38: return KEY_8;
  case 0x39: return KEY_9;

  // Special keys
  case 0x1B: return KEY_ESCAPE;
  case 0x20: return KEY_SPACE;
  case 0x0D: return KEY_RETURN;
  case 0x08: return KEY_BACKSPACE;
  case 0x26: return KEY_AUP;
  case 0x28: return KEY_ADOWN;
  case 0x25: return KEY_ALEFT;
  case 0x27: return KEY_ARIGHT;
  case 0x14: return KEY_CAPS;
  case 0x09: return KEY_TAB;

  // Modifier buttons
  case 0x10: return KEY_MOD_SHIFT;
  case 0x12: return KEY_MOD_ALT;
  case 0x11: return KEY_MOD_CONTROL;

  default: return KEY_UNDEFINED;
  }		   
};

char keycode_to_char(int keycode) {
  switch(keycode) {
  case KEY_A: return 'A';
  case KEY_B: return 'B';
  case KEY_C: return 'C';
  case KEY_D: return 'D';
  case KEY_E: return 'E';
  case KEY_F: return 'F';
  case KEY_G: return 'G';
  case KEY_H: return 'H';
  case KEY_I: return 'I';
  case KEY_J: return 'J';
  case KEY_K: return 'K';
  case KEY_L: return 'L';
  case KEY_M: return 'M';
  case KEY_N: return 'N';
  case KEY_O: return 'O';
  case KEY_P: return 'P';
  case KEY_Q: return 'Q';
  case KEY_R: return 'R';
  case KEY_S: return 'S';
  case KEY_T: return 'T';
  case KEY_U: return 'U';
  case KEY_V: return 'V';
  case KEY_W: return 'W';
  case KEY_X: return 'X';
  case KEY_Y: return 'Y';
  case KEY_Z: return 'Z';
  case KEY_0: return '0';
  case KEY_1: return '1';
  case KEY_2: return '2';
  case KEY_3: return '3';
  case KEY_4: return '4';
  case KEY_5: return '5';
  case KEY_6: return '6';
  case KEY_7: return '7';
  case KEY_8: return '8';
  case KEY_9: return '9';
  default: return '?';
  }
};

int is_modifier_key(int keycode) {
  switch(keycode) {
  case KEY_MOD_SHIFT:
  case KEY_MOD_ALT:
  case KEY_MOD_CONTROL:
    return 1;
  default: return 0;
  }
};


void win32_input_down(InputHandler* input, WPARAM wParam, LPARAM lParam) {
  if((lParam & (1 << 30)) > 0) return; // Key hold prevention

  int keycode = winkey_to_keycode(wParam);

  if(is_modifier_key(keycode)) {
    input->current_modifier |= keycode;
  }

  if(keycode) { // If keycode is valid
    input->keys[keycode] = 1;
    input->keys[keycode | input->current_modifier] = 1;
  }

};

void win32_input_up(InputHandler* input, WPARAM wParam, LPARAM lParam) {
  int keycode = winkey_to_keycode(wParam);

  if(is_modifier_key(keycode)) {
    input->current_modifier &= ~keycode;
  }

  if(keycode) { // if keycode is valid
    input->keys[keycode] = 0;
  }
};

int is_key_down(InputHandler* input, int keycode) {
  return input->keys[keycode];
};

int is_key_mod_down(InputHandler* input, int keycode, int modifiers) {
  return input->keys[keycode] && input->keys[keycode | modifiers];
};

