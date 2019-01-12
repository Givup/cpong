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

// TODO(Features, Ville): Audio

// TODO(Features, Ville): Collision between ball and paddles

// TODO(Features, Ville): Input

// TODO(Features, Ville): Support for textures

// TODO(Features, Ville): Some kind of particle system

int main(int argc, char** argv) {

  srand(time(NULL));

  Window window;
  if(create_window(&window, 1280, 720, "Hello, DOD!")){
    printf("Window creation failed!\n");
    return -1;
  }

  Matrix4 projection;
  set_ortho_mat4(&projection, 0.0f, (float)window.height, (float)window.width, 0.0f);

  OpenGLFunctions opengl;
  initialize_opengl_functions(&opengl);
  
  GLubyte* version_str = glGetString(GL_VERSION);
  printf("OpenGL version: %s\n", version_str);

  Shader shader;
  create_shader(&shader, vert_file, frag_file);
  use_shader(&shader);

  uniform_matrix4_shader(&shader, "proj", projection);

  glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

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
    
    loop_window(&window); // Loop through window messages

    update_game(&game, delta); // Update game

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
