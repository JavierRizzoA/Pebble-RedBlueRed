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
#include "player.h"

static GBitmap* player_red;
static GBitmap* player_blue;
static bool red;

void player_draw(GContext *ctx) {
  if(red) {
    graphics_draw_bitmap_in_rect(ctx, player_red, (GRect) {.origin = {56, 120}, .size = {32, 32}});
  } else {
    graphics_draw_bitmap_in_rect(ctx, player_blue, (GRect) {.origin = {56, 120}, .size = {32, 32}});
  }
}

bool player_get_status() {
  return red;
}

void player_flip() {
  red = !red;
}

void player_init() {
  player_red = gbitmap_create_with_resource(RESOURCE_ID_PLAYER_RED);
  player_blue = gbitmap_create_with_resource(RESOURCE_ID_PLAYER_BLUE);
  red = true;
}

void player_deinit() {
  gbitmap_destroy(player_red);
  gbitmap_destroy(player_blue);
}
