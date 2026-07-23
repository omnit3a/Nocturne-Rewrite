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

int e_world_data_initialize (e_world_object_t ** world_data_array, int indices) {
  *world_data_array = malloc(indices * sizeof(e_world_object_t));
  
  for (int index = 0 ; index < indices ; index++) {
    (*world_data_array)[index].id = 0;
    (*world_data_array)[index].name = "AIR";

    (*world_data_array)[index].pos.x = 0;
    (*world_data_array)[index].pos.y = 0;
    (*world_data_array)[index].pos.z = 0;
    (*world_data_array)[index].pos.i = index;
    
    (*world_data_array)[index].size = 1.0f;
    (*world_data_array)[index].volume = 1.0f;

    (*world_data_array)[index].physics.gravity = 1.0f;
    (*world_data_array)[index].physics.as_non_solid.dispersal_rate = 1.0f;
    (*world_data_array)[index].physics.is_solid = false;
    (*world_data_array)[index].physics.hardness = 0;

    (*world_data_array)[index].type = TYPE_BLOCK;
  }

  return 0;
};

int e_world_data_register (e_world_object_t ** world_data_array, int index) {
  (*world_data_array)[index].id = 0;
  (*world_data_array)[index].name = "AIR";
  
  (*world_data_array)[index].pos.x = 0;
  (*world_data_array)[index].pos.y = 0;
  (*world_data_array)[index].pos.z = 0;
  (*world_data_array)[index].pos.i = index;
  
  (*world_data_array)[index].size = 1.0f;
  (*world_data_array)[index].volume = 1.0f;
  
  (*world_data_array)[index].physics.gravity = 1.0f;
  (*world_data_array)[index].physics.as_non_solid.dispersal_rate = 1.0f;
  (*world_data_array)[index].physics.is_solid = false;
  (*world_data_array)[index].physics.hardness = 0;
  
  (*world_data_array)[index].type = TYPE_BLOCK;
  
  return 0;
}
