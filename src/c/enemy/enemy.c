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
#include <time.h>
#include <stdlib.h>
#include "enemy.h"

static GBitmap* enemy_blue;
static GBitmap* enemy_red;
static enemy_t *enemies;

static int rand_range(int max) {
  return rand() % max;
}

static void enemy_update(enemy_t *enemy) {
  if(enemy->alive) {
    enemy->y += 5;
    if(enemy->x == 63 || enemy->x == 65) {
      enemy->x = 64;
    } else if(enemy->x < 64) {
      enemy->x += 2;
    } else if(enemy->x > 64) {
      enemy->x -= 2;
    }
    if(enemy->y >= 104) {
      enemy->alive = false;
    }
  }
}

static void enemy_draw(enemy_t *enemy, GContext *ctx) {
  if(enemy->alive) graphics_draw_bitmap_in_rect(ctx, (enemy->red) ? enemy_red : enemy_blue, (GRect) {.origin = {enemy->x, enemy->y}, .size = {16, 16}});
}

void enemy_create() {
  enemy_t *e = malloc(sizeof(enemy_t));
  e->x = rand_range(144 - 16);
  e->y = -16;
  e->red = rand() & 1;
  e->alive = true;
  e->next = NULL;
  if(enemies == NULL) {
    e->prev = NULL;
    enemies = e;
  } else {
    enemy_t *prev = enemies;
    while(prev->next != NULL) {
      prev = prev->next;
    }
    prev->next = e;
    e->prev = prev;
  }
}

void enemy_delete(enemy_t *e) {
  if(e->prev == NULL) {
    enemies = e->next;
  } else {
    e->prev->next = e->next;
    if(e->next != NULL) e->next->prev = e->prev;
  }
  free(e);
}

static void enemies_delete_dead() {
  enemy_t *e = enemies;
  while(e != NULL) {
    if(!e->alive) {
      enemy_t *to_del = e;
      if(e->prev == NULL) {
        enemies = e->next;
        e->next->prev = NULL;
      } else {
        e->prev->next = e->next;
        if(e->next != NULL) e->next->prev = e->prev;
      }
      e = e->next;
      free(to_del);
    } else {
      e = e-> next;
    }
  }
}

static void delete_all_enemies() {
  enemy_t *e = enemies;
  while(e != NULL) {
    enemy_t *next = e->next;
    free(e);
    e = next;
  }
  enemies = NULL;
}

enemy_t *enemies_get() {
  return enemies;
}

void enemies_init() {
  srand(time(NULL));
  enemy_blue = gbitmap_create_with_resource(RESOURCE_ID_BLUE);
  enemy_red = gbitmap_create_with_resource(RESOURCE_ID_RED);
}

void enemies_deinit() {
  gbitmap_destroy(enemy_red);
  gbitmap_destroy(enemy_blue);
  delete_all_enemies();
}

void enemies_update() {
  enemies_delete_dead();
  enemy_t *e = enemies;
  while(e != NULL) {
    enemy_update(e);
    e = e->next;
  }
}

void enemies_draw(GContext *ctx) {
  enemy_t *e = enemies;
  while(e != NULL) {
    enemy_draw(e, ctx);
    e = e->next;
  }
}
