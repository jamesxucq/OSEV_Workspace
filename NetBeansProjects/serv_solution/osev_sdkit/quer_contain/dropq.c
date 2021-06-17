
#include "conattr.h"

#include "dropq.h"

//

int drop_conta_obje(riv_sessi_t *seion, rive_ha *stora_ha, char *osdb_name, char *table) {
    int drop_valu = stora_ha->dorp_conta(seion, table);
    dele_cattr(table, osdb_name);
    return drop_valu;
}
