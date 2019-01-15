#ifndef _GAME_H_
#define _GAME_H_

#include "render.h"
#include "vector.h"
#include "input_handler.h"

typedef struct {
  vec4 pos_size;
  vec4 color;
} Paddle;

typedef struct {
  float radius;  // Radius of ball
  float x, y;    // Position
  vec2 vel;      // Velocity
  vec4 color;    // Color
} Ball;

typedef struct {
  int width, height;
  Paddle paddles[2];
  Ball ball;

  int scores[2];
} Game;

extern void create_game(Game* game, int arena_w, int arena_h);
extern void update_game(Game* game, InputHandler* input_handler, float delta_time);
extern void render_game(Game* game, Renderer* renderer);
extern void free_game(Game* game);

#endif
