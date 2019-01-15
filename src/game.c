#include <math.h>
#include <stdio.h>

#include "game.h"
#include "opengl_impl.h"
#include "vector.h"

extern float randombif();

/*
  PADDLE
 */

void init_paddle(Paddle* paddle, int x, int y, int w, int h, vec4 color) {
  paddle->pos_size = make_vec4(x, y - h / 2, w, h);
  paddle->color = color;
};

/*
  BALL
 */

void init_ball(Ball* ball, int x, int y, float radius, vec4 color) {
  ball->x = x;
  ball->y = y;
  ball->radius = radius;
  ball->vel = make_vec2(-300.0f, randombif() * 300.0f);
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

  game->scores[0] = 0;
  game->scores[1] = 0;
};

int ball_collides_with_paddle(const Ball ball, const Paddle paddle, vec2* hit_normal, float* overlap) {
  // Implementation
  // Find the closest point from ball to paddle, and check the distance to that point
  // and if the distance is less than ball radius, there is collision
  
  float closestX, closestY;

  vec4 p = paddle.pos_size;

  // Calculate closest point
  float rect_min_x = get_x_vec4(p);
  float rect_max_x = get_x_vec4(p) + get_z_vec4(p);

  float rect_min_y = get_y_vec4(p);
  float rect_max_y = get_y_vec4(p) + get_w_vec4(p);

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

void move_paddle(const Game* game, Paddle* p, const vec4 amount) {
  add_vec4(&p->pos_size, amount);

  if(get_y_vec4(p->pos_size) < 0) {
    set_y_vec4(&p->pos_size, 0.0f);
  }
  if(get_y_vec4(p->pos_size) + get_w_vec4(p->pos_size) > game->height) {
    set_y_vec4(&p->pos_size, game->height - get_w_vec4(p->pos_size));
  }

};

void update_game(Game* game, InputHandler* input, float delta_time) {

  vec4 up = scale_vec4(make_vec4(0.0f, 300.0f, 0.0f, 0.0f), delta_time);
  vec4 down = scale_vec4(make_vec4(0.0f, -300.0f, 0.0f, 0.0f), delta_time);

  if(is_key_down(input, KEY_W)) {
    move_paddle(game, &game->paddles[0], up);
  }

  if(is_key_down(input, KEY_S)) {
    move_paddle(game, &game->paddles[0], down);
  }

  if(is_key_down(input, KEY_AUP)) {
    move_paddle(game, &game->paddles[1], up);
  }

  if(is_key_down(input, KEY_ADOWN)){
    move_paddle(game, &game->paddles[1], down);
  }

  // Ball update
  {
    Ball* ball = &game->ball;
    ball->x += ball->vel.v[0] * delta_time;
    ball->y += ball->vel.v[1] * delta_time;

    if(ball->x + ball->radius < 0.0f) {
      game->scores[1] += 1;
      init_ball(ball, game->width / 2, game->height / 2, ball->radius, game->paddles[1].color);
      ball->vel = mul_vec2(ball->vel, make_vec2(-1.0f, 1.0f));
    }
    else if(ball->x - ball->radius > game->width) {
      game->scores[0] += 1;
      init_ball(ball, game->width / 2, game->height / 2, ball->radius, game->paddles[0].color);
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

      game->ball.vel = mul_vec2(game->ball.vel, make_vec2(1.1f, 1.0f));
    }
  }

};

void render_paddle(const Paddle paddle, Renderer* renderer) {

  vec4 p = paddle.pos_size;

  float x = get_x_vec4(p);
  float y = get_y_vec4(p);
  float w = get_z_vec4(p);
  float h = get_w_vec4(p);

  render_rect(renderer, make_rrect(x + w / 2.0f, y + h / 2.0f, w, h), make_rmaterial_color(paddle.color));
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
