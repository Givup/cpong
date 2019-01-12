#ifndef _GAME_H_
#define _GAME_H_

#include "render.h"

typedef struct {
  int x, y;
  int width, height;
} Paddle;

typedef struct {
  float radius;
  float x, y;
  float vx, vy;
} Ball;

typedef struct {
  int width, height;
  Paddle paddles[2];
  Ball ball;
} Game;

extern void create_game(Game* game, int arena_w, int arena_h);
extern void update_game(Game* game, float delta_time);
extern void render_game(Game* game, Renderer* renderer);
extern void free_game(Game* game);

#endif
