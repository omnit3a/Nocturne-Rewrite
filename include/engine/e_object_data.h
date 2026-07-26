#ifndef E_OBJECT_DATA_H_
#define E_OBJECT_DATA_H_

// standard library
#include <stdbool.h>

// external libraries
#include <libs/fe/fe.h>

// internal headers

typedef enum {
  TYPE_BLOCK = 0,
  TYPE_ITEM
} e_object_data_type_e;

typedef enum {
  FI_SIZE = 0,
  FI_VOLUME,
  FI_GRAVITY,
  FI_FLOW,
  FI_DISPERSAL,
  FI_IS_SOLID,
  FI_HARDNESS,
  FI_TEXTURE,
  FI_PHYSICS
} e_object_data_fields_e;

typedef struct e_object_data_s {
  char * name;
  e_object_data_type_e type;
  fe_Object * init_callback;
  fe_Object * interact_callback;
  fe_Object * physics_callback;
  int id;
  int texture_uv;

  // amount of space this tile takes up within a specific x/y/z coordinate
  float size;
  // amount of space for other objects within a specific x/y/z coordinate
  float volume;
  
  struct physics_s {
    // rate at which it will fall to the ground
    float gravity;
    struct {
      float flow; // viscousity
      float dispersal; // how fast it will disperse as a gas
    } as_non_solid;
    bool is_solid;
    int hardness;
  } physics;
} e_object_data_t;

// sets aside space for world data array, and fill with empty blocks;
e_object_data_t * e_object_data_get_object_def(int index);
void e_object_data_set_object_def(e_object_data_t * object_definition, int index);
int e_object_data_def_initialize (int indices);
void e_object_data_object_def_free();
int e_object_data_def_register (int index, e_object_data_t object_definition);

#endif
