
/* 
 * File:   commo_directory.h
 * Author: James Xu
 *
 * Created on 2017.1.4, PM 4:48
 */

#ifndef COMMO_DIRECTORY_H
#define COMMO_DIRECTORY_H

#include "commo_macro.h"
#include "stri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern char _commo_directory_[MAX_PATH * 3];
#define _COMMO_DIRECTORY_     _commo_directory_
    inline char *commo_directory_init(char *directory);
    //
#define CREAT_OSDB_PATH(OSDB_PATH, OSDB_NAME) { \
    char *last_str = lscpy(OSDB_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, OSDB_NAME); }

#define CREAT_OSDB_SUBPA(OSDB_PATH, OSDB_NAME, SUB_PATH) { \
    char *last_str = lscpy(OSDB_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, SUB_PATH); }

#define CREAT_OSDB_SUBPA_EXT(LAST_STR, OSDB_PATH, OSDB_NAME, SUB_PATH) { \
    LAST_STR = lscpy(OSDB_PATH, _commo_directory_); \
    LAST_STR = lccpy(LAST_STR, '/'); \
    LAST_STR = lscpy(LAST_STR, OSDB_NAME); \
    LAST_STR = lccpy(LAST_STR, '/'); \
    LAST_STR = lscpy(LAST_STR, SUB_PATH); }

    //    
#define CREAT_CLASS_FILE(CLAS_PATH, OSDB_NAME, CLAS_NAME) { \
    char *last_str = lscpy(CLAS_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, CLAS_NAME); \
    lscpy(last_str, ".cla"); }

#define CREAT_CLATT_FILE(CLAS_PATH, OSDB_NAME, CLAS_NAME) { \
    char *last_str = lscpy(CLAS_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, CLAS_NAME); \
    lscpy(last_str, ".sdo"); }

#define CREAT_CACHE_FILE(CACH_PATH, OSDB_NAME, FILE_NAME) { \
    char *last_str = lscpy(CACH_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/cache/"); \
    lscpy(last_str, FILE_NAME); }

    //

#define CREAT_CONTAIN_PATH(ENGINE, CONT_PATH, OSDB_NAME) { \
    char *last_str = lscpy(CONT_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/contain/"); \
    lscpy(last_str, ENGINE); }

#define CREAT_CONTAIN_FILE(CONT_PATH, OSDB_NAME, FILE_NAME) { \
    char *last_str = lscpy(CONT_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/contain/"); \
    lscpy(last_str, FILE_NAME); }

#define ENGINE_CONTAIN_FILE(ENGINE, CONT_PATH, OSDB_NAME, FILE_NAME) { \
    char *last_str = lscpy(CONT_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/contain/"); \
    last_str = lscpy(last_str, ENGINE); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, FILE_NAME); }
    
#define CREAT_OBJECT_PATH(OBJE_PATH, OSDB_NAME, FILE_NAME) { \
    char *last_str = lscpy(OBJE_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/object/"); \
    lscpy(last_str, FILE_NAME); }

#define CREAT_OBJECT_FILE(OBJE_PATH, OSDB_NAME, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(OBJE_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/object/"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

#define CREAT_TEMPO_PATH(TEMP_PATH, OSDB_NAME, FILE_NAME) { \
    char *last_str = lscpy(TEMP_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/temp/"); \
    lscpy(last_str, FILE_NAME); }

#define CREAT_TEMPO_FILE(TEMP_PATH, OSDB_NAME, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(TEMP_PATH, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, OSDB_NAME); \
    last_str = lscpy(last_str, "/temp/"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

#ifdef __cplusplus
}
#endif

#endif /* COMMO_DIRECTORY_H */

