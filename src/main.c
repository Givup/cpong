#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gl/glcorearb.h>

#include "window.h"
#include "game.h"
#include "clock.h"
#include "opengl_impl.h"
#include "shader.h"
#include "matrix.h"
#include "render.h"

const char* vert_file = "shader.vert";
const char* frag_file = "shader.frag";

float randomf() {
  return (float)rand() / (float)RAND_MAX;
};

float randombif() {
  return (randomf() - 0.5f) * 2.0f;
};

int randomi(int max) {
  return (int)(randomf() * (float)max);
};

int randomi_range(int min, int max) {
  return min + (int)(randomf() * (float)(max - min));
};

void print_space_separated_values(char* values_string, const char* prefix) {
  printf("%s", prefix);
  while(*values_string != '\0') {
    if(*values_string == ' ') {
      printf("\n%s", prefix);
    } else {
      printf("%c", *values_string);
    }
    values_string++;
  }
};

// TODO(Features, Ville): Audio

// TODO(Features, Ville): Support for textures

int main(int argc, char** argv) {
  srand(time(NULL));

  InputHandler input_handler;

  Window window;
  if(create_window(&window, 1280, 720, "Hello, DOD!")){
    printf("Window creation failed!\n");
    return -1;
  }

  attach_input_handler(&window, &input_handler);

#if 0
  printf("\nSupported GL Extensions:\n");
  print_space_separated_values(window.gl_extensions, "\t");

  printf("\nSupported WGL Extensions:\n");
  print_space_separated_values(window.wgl_extensions, "\t");
#endif

  OpenGLFunctions opengl;
  initialize_opengl_functions(&opengl);

  Matrix4 projection;
  set_ortho_mat4(&projection, 0.0f, (float)window.height, (float)window.width, 0.0f);
  
  GLubyte* version_str = glGetString(GL_VERSION);
  printf("OpenGL version: %s\n", version_str);

  Shader shader;
  create_shader(&shader, vert_file, frag_file);
  use_shader(&shader);

  uniform_matrix4_shader(&shader, "proj", projection);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  Renderer renderer;
  init_renderer(&renderer, &shader, 100);

  Game game;
  create_game(&game, window.width, window.height);

  show_window(&window);

  Clock clock;
  start_clock(&clock);

  while(window.quit == 0) {
    // Update
    float delta = get_clock_delta_s(&clock); // Get elapsed time between this and last frame
    if(delta > 1.0f / 30.0f) delta = 1.0f / 30.0f;
    
    poll_window(&window); // Loop through window messages

    if(is_key_mod_down(&input_handler, KEY_Q, KEY_MOD_CONTROL)) {
      break;
    }

    update_game(&game, &input_handler, delta); // Update game

    // Rendering

    glClear(GL_COLOR_BUFFER_BIT);

    render_game(&game, &renderer);
    
    refresh_window(&window);
    
    reset_clock(&clock); // Reset clock
    Sleep(1); // Sleep for 1ms so cpu isn't always 100%
  }

  free_game(&game); // Deallocate game
  free_shader(&shader); // Free opengl shader
  free_opengl_functions(&opengl); // Free loaded opengl library
  free_window(&window); // Deallocate window
  return 0;
};
