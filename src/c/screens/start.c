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
#include "start.h"
#include "game.h"

static Window *start_window;
static TextLayer *title_layer;
static TextLayer *credit_layer;
static GFont title_font;
static GFont credit_font;
static GBitmap* icon_play;
static BitmapLayer *icon_play_layer;

static void start_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //window_stack_push(main_window, true);
  game_init();
  game_window_stack_push();
}

static void start_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, start_select_click_handler);
}

static void start_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  title_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_35));
  credit_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_16));
  title_layer = text_layer_create(GRect(0, 10, bounds.size.w, 150));
  credit_layer = text_layer_create(GRect(0, 140, bounds.size.w, 20));
  text_layer_set_background_color(title_layer, GColorClear);
  text_layer_set_background_color(credit_layer, GColorClear);
  text_layer_set_text_color(title_layer, GColorWindsorTan);
  text_layer_set_text_color(credit_layer, GColorWindsorTan);
  text_layer_set_font(title_layer, title_font);
  text_layer_set_font(credit_layer, credit_font);
  text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(credit_layer, GTextAlignmentCenter);
  text_layer_set_text(title_layer, "RED\nBLUE\nRED!");
  text_layer_set_text(credit_layer, "BY JAVIER RIZZO");
  layer_add_child(window_layer, text_layer_get_layer(title_layer));
  layer_add_child(window_layer, text_layer_get_layer(credit_layer));
  icon_play = gbitmap_create_with_resource(RESOURCE_ID_ICON_PLAY);
  icon_play_layer = bitmap_layer_create(GRect(134, 77, 10, 14));
  bitmap_layer_set_bitmap(icon_play_layer, icon_play);
  layer_add_child(window_layer, bitmap_layer_get_layer(icon_play_layer));
}

static void start_window_unload(Window *window) {
  text_layer_destroy(title_layer);
  text_layer_destroy(credit_layer);
  fonts_unload_custom_font(title_font);
  fonts_unload_custom_font(credit_font);
  bitmap_layer_destroy(icon_play_layer);
  gbitmap_destroy(icon_play);
}

void start_init() {
  start_window = window_create();
  window_set_background_color(start_window, GColorYellow);
  window_set_click_config_provider(start_window, start_click_config_provider);
  window_set_window_handlers(start_window, (WindowHandlers) {
      .load = start_window_load,
      .unload = start_window_unload
      });
}

void start_deinit() {
  window_destroy(start_window);
}

void start_window_stack_push() {
  window_stack_push(start_window, true);
}
