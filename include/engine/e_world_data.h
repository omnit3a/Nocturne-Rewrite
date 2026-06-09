#ifndef E_WORLD_DATA_H_
#define E_WORLD_DATA_H_

// standard library
#include <stdbool.h>

// external libraries

// internal headers

typedef enum {
  TYPE_BLOCK,
  TYPE_ITEM
} e_world_object_type_e;

typedef struct e_world_object_s {
  int id;
  char * name;

  int x_pos;
  int y_pos;
  int z_pos;

  // amount of space this tile takes up within a specific x/y/z coordinate
  float size;
  // amount of space for other objects within a specific x/y/z coordinate
  float volume;
  
  struct physics_s {
    // rate at which it will fall to the ground
    float gravity;
    union {
      float flow_rate; // viscousity
      float dispersal_rate; // how fast it will disperse as a gas
    } as_non_solid;
    bool is_solid;
    int hardness;
  } physics;
  
  e_world_object_type_e type;  
  
} e_world_object_t;

// sets aside space for world data array, and fill with empty blocks;
void e_world_data_initialize (e_world_object_t ** world_data_array, int width, int height, int depth);

#endif
