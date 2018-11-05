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
#include "end.h"

#define HISCORE_KEY 1

static Window *window;
static TextLayer *game_over_layer;
static TextLayer *score_layer;
static GFont game_over_font;
static GFont score_font;
static GBitmap* icon_dismiss;
static BitmapLayer *icon_dismiss_layer;
static char score_text[100];
static int hiscore;

static void set_score_text(int score) {
  if(persist_exists(HISCORE_KEY)) {
    hiscore = persist_read_int(HISCORE_KEY);
  } else {
    hiscore = 0;
    persist_write_int(HISCORE_KEY, hiscore);
  }
  if(score > hiscore) {
    hiscore = score;
    persist_write_int(HISCORE_KEY, hiscore);
  }
  snprintf(score_text, sizeof(score_text), "SCORE:\n%d\nHI SCORE:\n%d", score, hiscore);
  text_layer_set_text(score_layer, score_text);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_pop(true);
  end_deinit();
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_pop(true);
  end_deinit();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  game_over_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_35));
  game_over_layer = text_layer_create(GRect(0, 10, bounds.size.w, 80));
  text_layer_set_background_color(game_over_layer, GColorClear);
  text_layer_set_text_color(game_over_layer, GColorWindsorTan);
  text_layer_set_font(game_over_layer, game_over_font);
  text_layer_set_text_alignment(game_over_layer, GTextAlignmentCenter);
  text_layer_set_text(game_over_layer, "GAME\nOVER");
  layer_add_child(window_layer, text_layer_get_layer(game_over_layer));

  score_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_16));
  score_layer = text_layer_create(GRect(0, 100, bounds.size.w, 80));
  text_layer_set_background_color(score_layer, GColorClear);
  text_layer_set_text_color(score_layer, GColorWindsorTan);
  text_layer_set_font(score_layer, score_font);
  text_layer_set_text_alignment(score_layer, GTextAlignmentCenter);
  //text_layer_set_text(score_layer, "SCORE: \nHI SCORE: ");
  layer_add_child(window_layer, text_layer_get_layer(score_layer));

  icon_dismiss = gbitmap_create_with_resource(RESOURCE_ID_ICON_DISMISS);
  icon_dismiss_layer = bitmap_layer_create(GRect(129, 76, 15, 16));
  bitmap_layer_set_bitmap(icon_dismiss_layer, icon_dismiss);
  layer_add_child(window_layer, bitmap_layer_get_layer(icon_dismiss_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(game_over_layer);
  fonts_unload_custom_font(game_over_font);
  text_layer_destroy(score_layer);
  fonts_unload_custom_font(score_font);
  bitmap_layer_destroy(icon_dismiss_layer);
  gbitmap_destroy(icon_dismiss);
}

void end_init() {
  window = window_create();
  window_set_background_color(window, GColorYellow);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload
      });
}


void end_deinit() {
  window_destroy(window);
}

void end_window_stack_push(int score) {
  window_stack_push(window, true);
  set_score_text(score);
}
