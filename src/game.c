#include "game.h"
#include "opengl_impl.h"

/*
  PADDLE
 */

void init_paddle(Paddle* paddle, int x, int y, int w, int h, vec4 color) {
  paddle->x = x;
  paddle->y = y - h / 2;
  paddle->width = w;
  paddle->height = h;
  paddle->color = color;
};

/*
  BALL
 */

void init_ball(Ball* ball, int x, int y, float radius, vec4 color) {
  ball->x = x;
  ball->y = y;
  ball->radius = radius;
  ball->vx = -300.0f;
  ball->vy = -300.0f;
  ball->color = color;
};

/*
  GAME
 */

void create_game(Game* game, int arena_w, int arena_h) {
  game->width = arena_w;
  game->height = arena_h;

  vec4 ball_c;
  make_vec4(&ball_c, 0.0f, 0.7f, 0.0f, 1.0f);

  vec4 player_paddle_c;
  make_vec4(&player_paddle_c, 0.0f, 0.0f, 0.7f, 1.0f);

  vec4 enemy_paddle_c;
  make_vec4(&enemy_paddle_c, 0.7f, 0.0f, 0.0f, 1.0f);
  
  init_ball(&game->ball, arena_w / 2, arena_h / 2, 25.0f, ball_c);

  init_paddle(&game->paddles[0], 25, arena_h / 2, 25, 150, player_paddle_c);
  init_paddle(&game->paddles[1], arena_w - 50, arena_h / 2, 25, 150, enemy_paddle_c);
};

void update_game(Game* game, float delta_time) {
  // Ball update
  {
    Ball* ball = &game->ball;
    ball->x += ball->vx * delta_time;
    ball->y += ball->vy * delta_time;

    if(ball->x - ball->radius < 0.0f) {
      ball->x = ball->radius;
      ball->vx = -ball->vx;
    }
    else if(ball->x + ball->radius > game->width) {
      ball->x = game->width - ball->radius;
      ball->vx = -ball->vx;
    }

    if(ball->y - ball->radius < 0.0f) {
      ball->y = ball->radius;
      ball->vy = -ball->vy;
    }
    else if(ball->y + ball->radius > game->height) {
      ball->y = game->height - ball->radius;
      ball->vy = -ball->vy;
    }
  }
};

void render_paddle(const Paddle paddle, Renderer* renderer) {
  render_rect(renderer, make_rrect(paddle.x + paddle.width / 2, paddle.y + paddle.height / 2, paddle.width, paddle.height), make_rmaterial_color(paddle.color));
};

void render_ball(const Ball ball, Renderer* renderer) {
  render_circle(renderer, make_rcircle(ball.x, ball.y, ball.radius), make_rmaterial_color(ball.color));
};

void render_game(Game* game, Renderer* renderer) {
  render_paddle(game->paddles[0], renderer);
  render_paddle(game->paddles[1], renderer);
  render_ball(game->ball, renderer);
};

void free_game(Game* game) {
  
};

