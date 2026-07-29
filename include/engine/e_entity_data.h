#ifndef E_ENTITY_DATA_H_
#define E_ENTITY_DATA_H_

// standard library

// external libraries
#include <libs/fe/fe.h>

// internal headers


typedef enum {
  EF_SIZE = 0,
} e_entity_data_fields_e;

typedef struct e_entity_data_s {
  char * name;
  fe_Object * init_callback;
  fe_Object * behaviour_callback;
  fe_Object * physics_callback;
  int id;

  float size;
} e_entity_data_t;

#endif
