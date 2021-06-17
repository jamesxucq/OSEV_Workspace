
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiredtiger.h"
#include "wiredtiger_ext.h"
#pragma pack(1) 

typedef struct {
    unsigned int osev_unique;
    unsigned long long stoid;
} osv_oid_i;
#pragma pack() 
typedef WT_CURSOR riv_curso_t;
#pragma pack(1)

struct brole {
    osv_oid_i obje_oid;
    unsigned char role_type;
    char role_name[32];
    char priv_array[1024];
};
#pragma pack() 
struct brole _brole_sobj_;
int _brole_size_ = sizeof (struct brole);

void _bind_brole_(riv_curso_t *curso, struct brole *obje_data) {
    curso->set_key(curso, obje_data->obje_oid.stoid);
    curso->set_value(curso, obje_data->role_type, obje_data->role_name, obje_data->priv_array);
}

void _solve_brole_(struct brole *obje_data, riv_curso_t *curso) {
    char *dat1, *dat2;
    curso->get_key(curso, &(obje_data->obje_oid.stoid));
    curso->get_value(curso, &obje_data->role_type, &dat1, &dat2);
    memcpy(obje_data->role_name, dat1, 32);
    memcpy(obje_data->priv_array, dat2, 1024);
}

