
/* 
 * File:   hand_compi.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:47
 */

#ifndef HAND_COMPI_H
#define HAND_COMPI_H

#ifdef __cplusplus
extern "C" {
#endif

    void *compi_method(char *meth_name, char *osdb_path);
    void *compi_class(char *clasn, char *osdb_path);
    void *compi_package(char *package_path, char *osdb_path);

#ifdef __cplusplus
}
#endif

#endif /* HAND_COMPI_H */

