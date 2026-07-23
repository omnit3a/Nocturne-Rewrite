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

  struct pos_s {
    int x;
    int y;
    int z;
    int i; // one dimensional world index, precalculated
  } pos;

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
e_world_object_t * e_world_data_get_object_def_array();
void e_world_data_set_object_def_array(e_world_object_t ** object_definition_array);
int e_world_data_object_def_initialize (e_world_object_t ** object_definition_array, int indices);
int e_world_data_object_def_register (e_world_object_t ** object_definition_array, int index,
				      e_world_object_t object_definition);

#endif
