/* 
 * File:   execute.h
 * Author: James Xu
 *
 * Created on 2016.12.17, AM 9:04
 */

#ifndef EXECUTE_H
#define EXECUTE_H

#include "clie_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

//    
int method_execute(shel_resu *resu, shel_stat_t *shel_stat, osev_command *oscmd);


#ifdef __cplusplus
}
#endif

#endif /* EXECUTE_H */

