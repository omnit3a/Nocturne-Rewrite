// e_world_data.c
// <insert notes here>
// 
// 
// created: 09/06/2026

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// external libraries

// internal headers
#include <engine/e_object_data.h>
#include <engine/e_debug.h>

e_object_data_t * object_definitions;

e_object_data_t * e_object_data_get_object_def(int index) {
  return &(object_definitions[index]);
}

void e_object_data_set_object_def(e_object_data_t * object_definition, int index) {
  object_definitions[index] = *object_definition;
}

int e_object_data_def_initialize (int indices) {
  object_definitions = malloc(indices * sizeof(e_object_data_t));
  
  for (int index = 0 ; index < indices ; index++) {
    object_definitions[index].name = "";
    object_definitions[index].type = TYPE_BLOCK;
    object_definitions[index].init_callback = NULL;
    object_definitions[index].interact_callback = NULL;
    object_definitions[index].physics_callback = NULL;
    object_definitions[index].id = 0;
    object_definitions[index].texture_uv = 0;

    object_definitions[index].size = 0;
    object_definitions[index].volume = 0;
    object_definitions[index].physics.gravity = 0;
    object_definitions[index].physics.as_non_solid.flow = 0;
    object_definitions[index].physics.as_non_solid.dispersal = 0;
    object_definitions[index].physics.is_solid = false;
    object_definitions[index].physics.hardness = 0;
  }

  return 0;
};

void e_object_data_object_def_free() {
  free(object_definitions);
}

int e_object_data_def_register (int index, e_object_data_t object_definition) {
  object_definitions[index].name = object_definition.name;
  object_definitions[index].type = object_definition.type;
  object_definitions[index].init_callback = object_definition.init_callback;
  object_definitions[index].interact_callback = object_definition.interact_callback;
  object_definitions[index].physics_callback = NULL;
  object_definitions[index].id = index;
  object_definitions[index].texture_uv = index;

  object_definitions[index].size = 0;
  object_definitions[index].volume = 0;
  object_definitions[index].physics.gravity = 0;
  object_definitions[index].physics.as_non_solid.flow = 0;
  object_definitions[index].physics.as_non_solid.dispersal = 0;
  object_definitions[index].physics.is_solid = false;
  object_definitions[index].physics.hardness = 0;  
  
  return 0;
}
