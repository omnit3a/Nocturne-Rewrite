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
#include <time.h>

// external libraries

// internal headers
#include <project/p_world.h>
#include <engine/e_object_data.h>

p_world_data_t world_data;

void p_world_data_init(int width, int length, int depth) {
  const int world_data_size = width * length * depth;
  world_data.objects = malloc(sizeof(int) * world_data_size);
  world_data.width = width;
  world_data.length = length;
  world_data.depth = depth;
  for (int i = 0 ; i < world_data_size ; i++) {
    world_data.objects[i] = 0;    
  }
}

void p_world_data_free() {
  free(world_data.objects);
}

p_world_data_t * p_world_data_get_all() {
  return &world_data;
}

e_object_data_t p_world_data_get_object_at(int x, int y, int z) {
  int index = x + world_data.length * (y + world_data.depth * z);
  int id_at = world_data.objects[index];
  return *e_object_data_get_object_def(id_at);
}

void p_world_data_set_object_at(int x, int y, int z, e_object_data_t * object) {
  int index = x + world_data.width * (y + world_data.depth * z);
  world_data.objects[index] = object->id;
}

p_world_pos_t p_world_1d_to_3d (p_world_data_t * data, int index) {
  int z = index % data->depth;
  int y = (index / data->depth) % data->length;
  int x = index / (data->length * data->depth);

  p_world_pos_t result = {
    z, y, x
  };
  
  return result;
}

void p_world_generate_terrain(p_world_data_t * data) {
  const int world_data_size = data->width * data->length * data->depth;
  // how many layers of blocks there are. just for testing.
  // first entry is the amout of layers, the following are the blocks
  // used for each layer. will translate well to lisp
  for (int i = 0 ; i < world_data_size ; i++) {
    p_world_pos_t pos = p_world_1d_to_3d(data, i);
    int layer_block = 0;
    
    if (pos.z > (8 + i % 4)) {
      layer_block = 0;
    } else if (pos.z == (8 + i % 4)) {
      layer_block = 1;
    } else if (pos.z < (8 + i % 4)){
      layer_block = 2;
    }

    world_data.objects[i] = layer_block;
  }
}
