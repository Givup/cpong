#include <windows.h>
#include <assert.h>

typedef struct {
  int width;
  int height;
  int quit;
  LPCSTR class_name;
  HINSTANCE h_instance;
  HWND hwnd;
  HDC device_context;
  HGLRC gl_context;
  char* gl_extensions;
  char* wgl_extensions;
} Window;

extern LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern int create_window(Window* window, int width, int height, char* title);
extern int free_window(Window * window);

extern void show_window(Window* window);
extern int poll_window(Window* window);
extern void refresh_window(Window* window);
