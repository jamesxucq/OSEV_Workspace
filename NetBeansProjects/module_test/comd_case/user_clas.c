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

struct user {
    osv_oid_i obje_oid;
    char user_name[32];
    char password[32];
    char salt[16];
    char role_oid[96];
};
#pragma pack() 
struct user _user_sobj_;
int _user_size_ = sizeof (struct user);

void _bind_user_(riv_curso_t *curso, struct user *obje_data) {
    curso->set_key(curso, obje_data->obje_oid.stoid);
    curso->set_value(curso, obje_data->user_name, obje_data->password, obje_data->salt, obje_data->role_oid);
}

void _solve_user_(struct user *obje_data, riv_curso_t *curso) {
    curso->get_key(curso, &(obje_data->obje_oid.stoid));
    curso->get_value(curso, &obje_data->user_name, &obje_data->password, &obje_data->salt, &obje_data->role_oid);
}
