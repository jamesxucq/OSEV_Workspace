
/* 
 * File:   creat_shape.h
 * Author: James Xu
 *
 * Created on 2018.2.5, AM 9:57
 */

#ifndef CREAT_SHAPE_H
#define CREAT_SHAPE_H

#include "sha_common.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    uint32 build_shape_enviro(char *file_name, int32 isize);
    uint32 destroy_shape_enviro(char *file_name);



#ifdef __cplusplus
}
#endif

#endif /* CREAT_SHAPE_H */

