
/* 
 * File:   excep_code.h
 * Author: James Xu
 *
 * Created on 2017.9.20
 */

#ifndef EXCEP_CODE_H
#define EXCEP_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

#define EXCEP_LENG sizeof(unsigned int)

    //
#define     SERV_BASE      0x00010000

    //123456789abcde
#define     HAND_BASE      0x00030000
#define     INVA_PARA_EXCE      HAND_BASE|0x0001
#define     NOT_FOUND_CONTA     HAND_BASE|0x0003
#define     DROP_OBJE_EXCE      HAND_BASE|0x0005
#define     FACT_QUER_EXCE      HAND_BASE|0x0007
#define     CREAT_OBJE_EXCE     HAND_BASE|0x0009
#define     CREAT_CONTA_EXCE    HAND_BASE|0x000B
#define     EINVO_OBJE_EXCE     HAND_BASE|0x000D
#define     FIND_OBJE_EXCE      HAND_BASE|0x0011
#define     INSER_OBJE_EXCE     HAND_BASE|0x0013
#define     UPDAT_OBJE_EXCE     HAND_BASE|0x0015
#define     ECHO_OID_EXCE       HAND_BASE|0x0017
#define     RELOA_CLAS_EXCE     HAND_BASE|0x0019
#define     CLAS_INTEG_EXCE     HAND_BASE|0x001B
#define     STATI_OSDB_EXCE     HAND_BASE|0x001D
#define     CLAS_INFO_EXCE      HAND_BASE|0x0021
#define     CONTA_EXIST_EXCE    HAND_BASE|0x0023
#define     DROP_CLAS_EXCE      HAND_BASE|0x0025
#define     STAT_AUTH_EXCE      HAND_BASE|0x0027
#define     COMP_CLAS_EXCE      HAND_BASE|0x0029  
#define     CREAT_CLAS_EXCE     HAND_BASE|0x002B    
#define     CLAS_NOT_FOUND      HAND_BASE|0x002D    
    // #define     RELOA_METH_OK       HAND_BASE|0x0031
#define     RELOA_METH_EXCE     HAND_BASE|0x0033    
    // #define     DROP_METH_OK        HAND_BASE|0x0035
#define     DROP_METH_EXCE      HAND_BASE|0x0037    
    // #define     DROP_METH_EXCE   HAND_BASE|0x0039    
    // #define     CREAT_METH_OK       HAND_BASE|0x003B   
#define     COMP_METH_EXCE      HAND_BASE|0x003D    
#define     CREAT_METH_EXCE     HAND_BASE|0x0041    
#define     METH_NOT_FOUND      HAND_BASE|0x0043
// #define     GET_STATU_EXCE     HAND_BASE|0x0045 
    // #define     CLOSE_ODB_OK        HAND_BASE|0x0047  
#define     CLOSE_ODB_EXCE      HAND_BASE|0x0049  
    // #define     OPEN_ODB_OK         HAND_BASE|0x004B  
#define     OPEN_ODB_EXCE       HAND_BASE|0x004D  
#define     SHOW_ODB_EXCE       HAND_BASE|0x0051  
#define     QUER_ASTAT_EXCE     HAND_BASE|0x0053  
#define     SHOW_AODB_EXCE      HAND_BASE|0x0055
#define     CREAT_INHER_EXCE    HAND_BASE|0x0057
// #define     SET_STATU_EXCE     HAND_BASE|0x0059 
    //
#define     FIND_ROLE_EXCE    HAND_BASE|0x0059
#define     ADDI_ROLE_EXCE    HAND_BASE|0x005B 
#define     ROLE_USED_EXCE    HAND_BASE|0x005D 
#define     DELE_ROLE_EXCE    HAND_BASE|0x0061 
#define     DIST_OID_EXCE     HAND_BASE|0x0063
#define     LOAD_ROLE_EXCE    HAND_BASE|0x0065
#define     REVK_PRIV_EXCE    HAND_BASE|0x0067 
#define     FIND_USER_EXCE    HAND_BASE|0x0069 
#define     GRAN_PRIV_EXCE    HAND_BASE|0x006B 
#define     DELE_USER_EXCE    HAND_BASE|0x006D 
#define     ADDI_USER_EXCE    HAND_BASE|0x0071 
#define     REVK_ROLE_EXCE    HAND_BASE|0x0073 
#define     GRAN_ROLE_EXCE    HAND_BASE|0x0075 
#define     USER_ROLE_EXIS    HAND_BASE|0x0077 
#define     ROLE_PRIV_EXIS    HAND_BASE|0x0079 
#define     OSDB_ADMIN_EXCE   HAND_BASE|0x007B 
    //#define     _EXCE    HAND_BASE|0x007D 
    //#define     _EXCE    HAND_BASE|0x0081 
    //#define     _EXCE    HAND_BASE|0x0083 
    //#define     _EXCE    HAND_BASE|0x0085 
    //#define     _EXCE    HAND_BASE|0x0087 
    //#define     _EXCE    HAND_BASE|0x0089 
    //#define     _EXCE    HAND_BASE|0x008B 
    //#define     _EXCE    HAND_BASE|0x008D 
#define     OSEV_ATTACH_EXCE   HAND_BASE|0xFFFF 



    //
#define     RIVE_BASE      0x00050000


#ifdef __cplusplus
}
#endif

#endif /* EXCEP_CODE_H */

