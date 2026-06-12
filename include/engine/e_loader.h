#ifndef E_LOADER_H_
#define E_LOADER_H_

// standard library

// external libraries

// internal headers
#include <engine/e_world_data.h>

int e_loader_source_object_defs (e_world_object_t ** definitions, int min, int max);
// allow for hotloading of object defs >:)
int e_loader_refresh_object_defs (e_world_object_t ** definitions, int max);
int e_loader_offload_object_defs (e_world_object_t ** definitions);

#endif
