
/* 
 * File:   check_command.h
 * Author: James Xu
 *
 * Created on 2017.5.21, PM3:43
 */

#ifndef CHECK_COMMAND_H
#define CHECK_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

// 0:success 0x01:exception -1:error
    int check_method(osev_command *oscmd, uint32 shell_mode, uint32 run_level);
    
    //
    int check_extend(osev_command *oscmd, uint32 shell_mode, uint32 run_level);



#ifdef __cplusplus
}
#endif

#endif /* CHECK_COMMAND_H */

