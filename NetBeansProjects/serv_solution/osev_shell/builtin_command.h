
#ifndef BUILTIN_COMMAND_H
#define BUILTIN_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "parse_command.h"

    //    
    uint32 builtin_command(osev_command *oscmd, uint32 shell_mode);
    uint32 clie_run_level(osev_command *oscmd, uint32 last_leve);

#ifdef __cplusplus
}
#endif

#endif /* BUILTIN_COMMAND_H */

