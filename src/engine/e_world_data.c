// e_world_data.c
// <insert notes here>
// 
// 
// created: 09/06/2026

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries

// internal headers
#include <engine/e_world_data.h>
#include <engine/e_debug.h>

static e_world_object_t * object_definitions;

e_world_object_t * e_world_data_get_object_def_array() {
  return object_definitions;
}

void e_world_data_set_object_def_array(e_world_object_t ** object_definition_array) {
  object_definitions = *object_definition_array;
}

int e_world_data_object_def_initialize (e_world_object_t ** object_definition_array, int indices) {
  *object_definition_array = malloc(indices * sizeof(e_world_object_t));
  
  for (int index = 0 ; index < indices ; index++) {
    (*object_definition_array)[index].id = 0;
    (*object_definition_array)[index].name = "AIR";
  
    (*object_definition_array)[index].pos.x = 0;
    (*object_definition_array)[index].pos.y = 0;
    (*object_definition_array)[index].pos.z = 0;
    (*object_definition_array)[index].pos.i = index;
  
    (*object_definition_array)[index].size = 1.0f;
    (*object_definition_array)[index].volume = 1.0f;
  
    (*object_definition_array)[index].physics.gravity = 1.0f;
    (*object_definition_array)[index].physics.as_non_solid.dispersal_rate = 1.0f;
    (*object_definition_array)[index].physics.is_solid = false;
    (*object_definition_array)[index].physics.hardness = 0;
  
    (*object_definition_array)[index].type = TYPE_BLOCK;
  }

  return 0;
};

int e_world_data_object_def_register (e_world_object_t ** object_definition_array, int index,
				      e_world_object_t object_definition) {
  (*object_definition_array)[index].id = index;
  (*object_definition_array)[index].name = object_definition.name;
  
  (*object_definition_array)[index].pos.x = 0;
  (*object_definition_array)[index].pos.y = 0;
  (*object_definition_array)[index].pos.z = 0;
  (*object_definition_array)[index].pos.i = index;
  
  (*object_definition_array)[index].size = object_definition.size;
  (*object_definition_array)[index].volume = object_definition.volume;
  
  (*object_definition_array)[index].physics.gravity = object_definition.physics.gravity;
  (*object_definition_array)[index].physics.as_non_solid.dispersal_rate = object_definition.physics.as_non_solid.dispersal_rate;
  (*object_definition_array)[index].physics.is_solid = object_definition.physics.is_solid;
  (*object_definition_array)[index].physics.hardness = object_definition.physics.hardness;
  
  (*object_definition_array)[index].type = object_definition.type;
  
  return 0;
}
