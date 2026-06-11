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

void e_world_data_initialize (e_world_object_t ** world_data_array, int width, int height, int depth) {
  if (*world_data_array != NULL) {
    e_debug_already_initialized(E_DEBUG_SUBSYSTEM_WORLD_DATA, "Unknown world data state, re-initializing");
  }

  int total_world_indices = width * height * depth;
  *world_data_array = malloc(total_world_indices * sizeof(e_world_object_t));

  for (int world_index = 0 ; world_index < total_world_indices ; world_index++) {
    (*world_data_array)[world_index].id = 0;
    (*world_data_array)[world_index].name = "AIR";

    // TODO: 1d index (world_index) to XYZ coordinates for world_object
    
    (*world_data_array)[world_index].size = 1.0f;
    (*world_data_array)[world_index].volume = 1.0f;

    (*world_data_array)[world_index].physics.gravity = 1.0f;
    (*world_data_array)[world_index].physics.as_non_solid.dispersal_rate = 1.0f;
    (*world_data_array)[world_index].physics.is_solid = false;
    (*world_data_array)[world_index].physics.hardness = 0;

    (*world_data_array)[world_index].type = TYPE_BLOCK;
  }
};
