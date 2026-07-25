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
#include <engine/e_world_data.h>
#include <engine/e_debug.h>

e_world_object_t * object_definitions;

e_world_object_t * e_world_data_get_object_def(int index) {
  return &(object_definitions[index]);
}

void e_world_data_set_object_def(e_world_object_t * object_definition, int index) {
  object_definitions[index] = *object_definition;
}

int e_world_data_object_def_initialize (int indices) {
  object_definitions = malloc(indices * sizeof(e_world_object_t));
  
  for (int index = 0 ; index < indices ; index++) {
    object_definitions[index].name = "";
    object_definitions[index].type = TYPE_BLOCK;
    object_definitions[index].callback = NULL;
    object_definitions[index].id = 0;
    object_definitions[index].texture_uv = 0;   
  }

  return 0;
};

void e_world_data_object_def_free() {
  free(object_definitions);
}

int e_world_data_object_def_register (int index, e_world_object_t object_definition) {
  object_definitions[index].name = object_definition.name;
  object_definitions[index].type = object_definition.type;
  object_definitions[index].callback = object_definition.callback;
  object_definitions[index].id = index;
  object_definitions[index].texture_uv = index;
  
  //printf("%s\n", object_definitions[index].callback);
  
  return 0;
}
