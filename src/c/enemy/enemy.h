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

typedef struct enemy_t {
  int x;
  int y;
  bool red;
  bool alive;
  struct enemy_t *next;
  struct enemy_t *prev;
} enemy_t;

void enemies_init();

void enemies_deinit();

void enemy_create();

void enemies_update();

enemy_t *enemies_get();

void enemies_draw(GContext *ctx);
