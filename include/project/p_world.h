#ifndef P_WORLD_H_
#define P_WORLD_H_

// standard library

// external libraries

// internal headers
#include <engine/e_object_data.h>

// allows for extensible world data
typedef struct p_world_data_s {
  int * objects;
  int width;
  int length;
  int depth;
} p_world_data_t;

typedef struct p_world_pos_s {
  int x;
  int y;
  int z;
} p_world_pos_t;

void p_world_data_init(int width, int length, int depth);
void p_world_data_free();
p_world_data_t * p_world_data_get_all();
e_object_data_t p_world_data_get_object_at(int x, int y, int z);
void p_world_data_set_object_at(int x, int y, int z, e_object_data_t * object);

p_world_pos_t p_world_1d_to_3d (p_world_data_t * data, int index);
void p_world_generate_terrain(p_world_data_t * data);

#endif
