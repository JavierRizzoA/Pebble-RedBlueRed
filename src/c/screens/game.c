/* 
 * This file is part of Pebble-RedBlueRed
 * (https://github.com/JavierRizzoA/Pebble-RedBlueRed).
 * Copyright (c) 2018 Javier Rizzo-Aguirre.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <pebble.h>
#include "game.h"
#include "../player/player.h"
#include "../enemy/enemy.h"
#include "end.h"

static Window *window;
static Layer *game_layer;
static int timeSinceEnemy;
static int speed;
static AppTimer *timer;
static int score;
static TextLayer *score_layer;
static GFont score_font;
char score_a[20];

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  player_flip();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  player_flip();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  player_flip();
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_pop(true);
  game_deinit();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

static void update_score() {
  snprintf(score_a, sizeof(score_a), "%d", score);
  text_layer_set_text(score_layer, score_a);
}

static void check_collision() {
  enemy_t *e = enemies_get();
  if(e!= NULL && !e->alive) {
    if(e->red == player_get_status()) {
      score++;
      update_score();
    } else {
      end_init();
      window_stack_pop(true);
      end_window_stack_push(score);
      game_deinit();
    }
  }
}

static void draw(Layer *layer, GContext *ctx) {
  enemies_draw(ctx);
  player_draw(ctx);
  check_collision();
}

static void update() {
  timeSinceEnemy += 50;
  if(timeSinceEnemy >= speed) {
    enemy_create();
    timeSinceEnemy = 0;
    speed -= 10;
    if(speed < 260) speed = 260;
  }
  enemies_update();
  timer = app_timer_register(50, update, NULL);
  layer_mark_dirty(game_layer);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  game_layer = layer_create(bounds);
  layer_add_child(window_layer, game_layer);
  layer_set_update_proc(game_layer, draw);
  timer = app_timer_register(50, update, NULL);
  score_layer = text_layer_create(GRect(0, 10, bounds.size.w - 10, 35));
  text_layer_set_background_color(score_layer, GColorClear);
  text_layer_set_text_color(score_layer, GColorWindsorTan);
  score_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_28));
  text_layer_set_font(score_layer, score_font);
  text_layer_set_text_alignment(score_layer, GTextAlignmentRight);
  layer_add_child(game_layer, text_layer_get_layer(score_layer));
  update_score();
}

static void window_unload(Window *window) {
  text_layer_destroy(score_layer);
  layer_destroy(game_layer);
  fonts_unload_custom_font(score_font);
}

void game_init() {
  score = 0;
  timeSinceEnemy = 0;
  speed = 1000;
  enemies_init();
  player_init();
  window = window_create();
  window_set_background_color(window, GColorYellow);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload
      });
}

void game_deinit() {
  app_timer_cancel(timer);
  enemies_deinit();
  player_deinit();
  window_destroy(window);
}

void game_window_stack_push() {
  window_stack_push(window, true);
}
