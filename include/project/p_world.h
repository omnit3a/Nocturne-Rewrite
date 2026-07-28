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
  int height;
  int depth;
} p_world_data_t;

void p_world_data_init(int width, int height, int depth);
void p_world_data_free();
p_world_data_t * p_world_data_get_all();
e_object_data_t p_world_data_get_object_at(int x, int y, int z);
void p_world_data_set_object_at(int x, int y, int z, e_object_data_t * data);

#endif
