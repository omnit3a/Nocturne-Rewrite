// p_world.c
// handles world state
// 
// 
// created: 28/07/2026

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// external libraries

// internal headers
#include <project/p_world.h>
#include <engine/e_object_data.h>

p_world_data_t world_data;

void p_world_data_init(int width, int height, int depth) {
  world_data.objects = malloc(sizeof(int) * width * height * depth);
  world_data.width = width;
  world_data.height = height;
  world_data.depth = depth;
  for (int i = 0 ; i < width * height * depth ; i++) {
    world_data.objects[i] = i % 3;    
  }
}

void p_world_data_free() {
  free(world_data.objects);
}

p_world_data_t * p_world_data_get_all() {
  return &world_data;
}

e_object_data_t p_world_data_get_object_at(int x, int y, int z) {
  int index = x + world_data.width * (y + world_data.height * z);
  int id_at = world_data.objects[index];
  return *e_object_data_get_object_def(id_at);
}

void p_world_data_set_data_at(int x, int y, int z, e_object_data_t * data) {
  int index = x + world_data.width * (y + world_data.height * z);
  world_data.objects[index] = data->id;
}
