#ifndef _GAME_H_
#define _GAME_H_

#define NUM_OBSTACLES 32

#include "render.h"
#include "vector.h"

typedef struct {
  int x, y;
  int width, height;
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

  Paddle obstacles[NUM_OBSTACLES];

  Ball ball;
} Game;

extern void create_game(Game* game, int arena_w, int arena_h);
extern void update_game(Game* game, float delta_time);
extern void render_game(Game* game, Renderer* renderer);
extern void free_game(Game* game);

#endif
