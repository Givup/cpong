#include <math.h>
#include <stdio.h>

#include "game.h"
#include "opengl_impl.h"
#include "vector.h"

extern int randomi_range(int, int);

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
  ball->vel = make_vec2(-300.0f, -300.0f);
  ball->color = color;
};

/*
  GAME
 */

void create_game(Game* game, int arena_w, int arena_h) {
  game->width = arena_w;
  game->height = arena_h;

  vec4 ball_c = make_vec4(0.0f, 0.7f, 0.0f, 1.0f);
  vec4 player_paddle_c = make_vec4(0.0f, 0.0f, 0.7f, 1.0f);
  vec4 enemy_paddle_c = make_vec4(0.7f, 0.0f, 0.0f, 1.0f);
  vec4 obstacle_c = make_vec4(0.7f, 0.7f, 0.3f, 1.0f);
  
  init_ball(&game->ball, arena_w / 2, arena_h / 2, 25.0f, ball_c);

  init_paddle(&game->paddles[0], 25, arena_h / 2, 25, 150, player_paddle_c);
  init_paddle(&game->paddles[1], arena_w - 50, arena_h / 2, 25, 150, enemy_paddle_c);
};

int ball_collides_with_paddle(const Ball ball, const Paddle paddle, vec2* hit_normal, float* overlap) {
  // Implementation
  // Find the closest point from ball to paddle, and check the distance to that point
  // and if the distance is less than ball radius, there is collision
  
  float closestX, closestY;

  // Calculate closest point
  float rect_min_x = paddle.x;
  float rect_max_x = paddle.x + paddle.width;

  float rect_min_y = paddle.y;
  float rect_max_y = paddle.y + paddle.height;

  closestX = min(max(ball.x, rect_min_x), rect_max_x);
  closestY = min(max(ball.y, rect_min_y), rect_max_y);
  
  float d_x = closestX - ball.x;
  float d_y = closestY - ball.y;

  float d = (float)sqrt(d_x * d_x + d_y * d_y);

  if(d < ball.radius) {
    // Calculate hit normal
    vec2 norm = make_vec2(d_x, d_y);
    norm = normalize_vec2(norm);
    set_vec2(hit_normal, norm.v[0], norm.v[1]);
    *overlap = ball.radius - d;
    return 1;
  }
  return 0;
};

void update_game(Game* game, float delta_time) {
  // Ball update
  {
    Ball* ball = &game->ball;
    ball->x += ball->vel.v[0] * delta_time;
    ball->y += ball->vel.v[1] * delta_time;

    if(ball->x - ball->radius < 0.0f) {
      ball->x = ball->radius;
      ball->vel.v[0] = -ball->vel.v[0];
    }
    else if(ball->x + ball->radius > game->width) {
      ball->x = game->width - ball->radius;
      ball->vel.v[0] = -ball->vel.v[0];
    }

    if(ball->y - ball->radius < 0.0f) {
      ball->y = ball->radius;
      ball->vel.v[1] = -ball->vel.v[1];
    }
    else if(ball->y + ball->radius > game->height) {
      ball->y = game->height - ball->radius;
      ball->vel.v[1] = -ball->vel.v[1];
    }
  }

  // Check for collision
  {
    vec2 normal;
    float overlap;
    if(ball_collides_with_paddle(game->ball, game->paddles[0], &normal, &overlap) || ball_collides_with_paddle(game->ball, game->paddles[1], &normal, &overlap)) {
      vec2 reflected = reflect_vec2(game->ball.vel, normal);
      set_vec2(&game->ball.vel, reflected.v[0], reflected.v[1]);

      vec2 vel_normalized = normalize_vec2(game->ball.vel);
      vel_normalized = scale_vec2(vel_normalized, overlap);
      game->ball.x += vel_normalized.v[0]; 
      game->ball.y += vel_normalized.v[1];
    }
  }

};

void render_paddle(const Paddle paddle, Renderer* renderer) {
  render_rect(renderer, make_rrect(paddle.x + paddle.width / 2.0f, paddle.y + paddle.height / 2.0f, paddle.width, paddle.height), make_rmaterial_color(paddle.color));
};

void render_ball(const Ball ball, Renderer* renderer) {
  render_circle(renderer, make_rcircle(ball.x, ball.y, ball.radius), make_rmaterial_color(ball.color));
};

void render_game(Game* game, Renderer* renderer) {
  render_ball(game->ball, renderer);

  render_paddle(game->paddles[0], renderer);
  render_paddle(game->paddles[1], renderer);
};

void free_game(Game* game) {
};
