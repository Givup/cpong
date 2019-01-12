#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "window.h"
#include "gl/glcorearb.h"
#include "gl/wglext.h"

void PrintErrorString() {
  DWORD error = GetLastError();
  char error_str[256];
  FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
		error_str,
		256,
		NULL
		);

  printf("Error: %s\n", error_str);
};

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  if(msg != 36 && msg != 129 && msg != 131 && msg != 1) {
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (msg) {
    case WM_CLOSE:
    case WM_DESTROY:
      window->quit = 1;
      return 0;
    }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
};

int create_window(Window* window, int width, int height, char* title) {

  HINSTANCE h_instance = GetModuleHandle(NULL);

  window->width = width;
  window->height = height;
  window->quit = 0;
  window->h_instance = h_instance;
  window->class_name = "PongClassName";

  WNDCLASS wnd = { 0 };
  wnd.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  wnd.lpfnWndProc = window_proc;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = h_instance;
  wnd.hIcon = NULL;
  wnd.hCursor = NULL;
  wnd.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
  wnd.lpszMenuName = NULL;
  wnd.lpszClassName = window->class_name;

  if(RegisterClass(&wnd) == 0) {
    printf("Failed to register class for window!\n");
    return 1;
  }

  HWND hwnd = CreateWindowEx(
			     WS_EX_OVERLAPPEDWINDOW, // dwExStyle
			     window->class_name,     // lpClassName
			     title,                  // lpWindowName
			     WS_OVERLAPPEDWINDOW,    // dwStyle
			     0, 0, width, height,    // x, y, w, h
			     NULL,                   // hwndParent
			     NULL,                   // hMenu
			     h_instance,             // hInstance
			     NULL                    // lpParam
			     
			     );

  if(hwnd == NULL) {
    printf("Failed to create window!\n");
    return 2;
  }

  window->hwnd = hwnd;

  SetWindowLongPtr( hwnd, GWLP_USERDATA, (long)window );

  // OpenGL context creation
  PIXELFORMATDESCRIPTOR pfd = {
			       sizeof(PIXELFORMATDESCRIPTOR),
			       1,
			       PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			       PFD_TYPE_RGBA,
			       32,
			       0, 0, 0, 0, 0, 0,
			       0,
			       0,
			       0,
			       0, 0, 0, 0,
			       24,
			       8,
			       0,
			       PFD_MAIN_PLANE,
			       0,
			       0, 0, 0
  };

  HDC dc = GetDC(hwnd);
  
  int suggested_format = ChoosePixelFormat(dc, &pfd);

  if(suggested_format == 0) {
    printf("Failed to choose a pixel format!\n");
    return 3;
  }

  SetPixelFormat(dc, suggested_format, &pfd);

  window->device_context = dc;

  HGLRC fake_gl_context = wglCreateContext(dc);

  if(fake_gl_context == NULL) {
    printf("Failed to create fake OpenGL context!\n");
    PrintErrorString();
    return 4;
  }

  wglMakeCurrent(dc, fake_gl_context);

  HANDLE glLib = LoadLibrary("opengl32.dll");
  PROC glGetString = GetProcAddress(glLib, "glGetString");

  assert(glGetString != 0);

  char* extensions = (char*)glGetString(GL_EXTENSIONS);
  if(extensions == 0) {
    printf("Failed to query OpenGL extensions.\n");
    return 5;
  }
  
  FreeLibrary(glLib);

  int ext_length = strlen(extensions);
  window->gl_extensions = (char*)malloc(ext_length);
  window->gl_extensions = strcpy(window->gl_extensions, extensions);


  char* (*f_wglGetExtensionsStringARB)(HDC);
  f_wglGetExtensionsStringARB = wglGetProcAddress("wglGetExtensionsStringARB");
  assert(f_wglGetExtensionsStringARB != 0);

  if(f_wglGetExtensionsStringARB == NULL) {
    printf("Failed to get WGL extenions string function!");
    return 5;
  }

  char* wgl_extensions = f_wglGetExtensionsStringARB(dc);
  
  if(wgl_extensions == 0) {
    printf("Failed to get WGL extensions string!\n");
    return 6;
  }
  window->wgl_extensions = wgl_extensions;

  BOOL (*f_wglChoosePixelFormatARB)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
  f_wglChoosePixelFormatARB = wglGetProcAddress("wglChoosePixelFormatARB");
  assert(f_wglChoosePixelFormatARB != 0);

  const int attribList[] = {
			    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			    WGL_COLOR_BITS_ARB, 32,
			    WGL_DEPTH_BITS_ARB, 24,
			    WGL_STENCIL_BITS_ARB, 8,
			    0 // End
  };

  int wglPixelFormat;
  UINT numFormats;

  if(f_wglChoosePixelFormatARB(dc, attribList, NULL, 1, &wglPixelFormat, &numFormats) == FALSE) {
    printf("Failed to choose pixel format ARB!\n");
    return 7;
  }

  SetPixelFormat(dc, wglPixelFormat, &pfd);

  HGLRC (*f_wglCreateContextAttribsARB)(HDC, HGLRC, const int*);
  f_wglCreateContextAttribsARB = wglGetProcAddress("wglCreateContextAttribsARB");
  assert(f_wglCreateContextAttribsARB != 0);

  const int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 0,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0 // End
  };

  HGLRC real_context = f_wglCreateContextAttribsARB(dc, NULL, contextAttribs);

  if(real_context == NULL) {
    printf("Failed to create real GL context!\n");
    return 8;
  };


  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(fake_gl_context);

  wglMakeCurrent(dc, real_context);
  
  window->gl_context = real_context;

  return 0;
};

int free_window(Window * window) {
  wglMakeCurrent(NULL, NULL);
  if(wglDeleteContext(window->gl_context) == FALSE) {
    printf("Failed to destroy OpenGL context!\n");
    return 3;
  }


  if(DestroyWindow(window->hwnd) == 0) {
    printf("Failed to destroy window!\n");
    return 2;
  }

  if(UnregisterClass(window->class_name, window->h_instance) == 0) {
    printf("Failed to unregister class!\n");
    return 1;
  }
  return 0;
};

void show_window(Window* window) {
  ShowWindow(window->hwnd, SW_SHOW);
};

int poll_window(Window* window) {
  MSG msg;
  while(PeekMessage(&msg, window->hwnd, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 1;
};

void refresh_window(Window* window) {
  SwapBuffers(window->device_context);
};
