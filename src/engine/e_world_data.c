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

int e_world_data_initialize (e_world_object_t ** world_data_array, int width, int height, int depth) {
  const int world_data_init_steps = 2;
  int world_data_init_stage = 1;

  const int w = width;
  const int h = height;
  const int wh = width * height;
  
  int total_world_indices = width * height * depth;
  *world_data_array = malloc(total_world_indices * sizeof(e_world_object_t));
  world_data_init_stage = e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_WORLD_DATA, world_data_init_stage, world_data_init_steps, "Allocated memory for world data");
  
  for (int world_index = 0 ; world_index < total_world_indices ; world_index++) {
    (*world_data_array)[world_index].id = 0;
    (*world_data_array)[world_index].name = "AIR";

    // three dimensional components of the one dimensional world_index
    int index_zc = world_index / wh;
    int index_yc = (world_index - index_zc * wh) / w;
    int index_xc = world_index - w * (index_yc + h * index_zc);

    (*world_data_array)[world_index].pos.x = index_xc;
    (*world_data_array)[world_index].pos.y = index_yc;
    (*world_data_array)[world_index].pos.z = index_zc;
    (*world_data_array)[world_index].pos.i = world_index;
    
    (*world_data_array)[world_index].size = 1.0f;
    (*world_data_array)[world_index].volume = 1.0f;

    (*world_data_array)[world_index].physics.gravity = 1.0f;
    (*world_data_array)[world_index].physics.as_non_solid.dispersal_rate = 1.0f;
    (*world_data_array)[world_index].physics.is_solid = false;
    (*world_data_array)[world_index].physics.hardness = 0;

    (*world_data_array)[world_index].type = TYPE_BLOCK;
  }

  world_data_init_stage = e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_WORLD_DATA, world_data_init_stage, world_data_init_steps, "Initialized world data");

  return 0;
};
