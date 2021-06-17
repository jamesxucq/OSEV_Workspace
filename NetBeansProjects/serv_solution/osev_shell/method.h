
#ifndef METHOD_H
#define METHOD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "parse_command.h"
#include "clie_struct.h"

    //
    int prepare_method(osev_command *oscmd, uint32 shell_mode, uint32 run_level);

    //
    int finish_method(osev_command *oscmd, shel_resu *resu);
    int finish_extend(osev_command *oscmd, shel_resu *resu);


#ifdef __cplusplus
}
#endif

#endif /* METHOD_H */

