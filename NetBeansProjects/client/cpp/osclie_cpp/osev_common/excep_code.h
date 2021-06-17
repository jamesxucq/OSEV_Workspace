
/* 
 * File:   excep_code.h
 * Author: Administrator
 *
 * Created on 2017.9.20
 */

#ifndef EXCEP_CODE_H
#define EXCEP_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

#define EXCEP_LEN sizeof(unsigned int)
    
    //
#define     SERV_BASE      0x00010000
    
    //
#define     HAND_BASE      0x00030000
#define     INVA_PARA_EXCE      HAND_BASE|0x0001
#define     NOT_FOUND_CONTA     HAND_BASE|0x0003
#define     DROP_OBJE_EXCE      HAND_BASE|0x0005
#define     FACT_QUER_EXCE      HAND_BASE|0x0007
#define     CREAT_OBJE_EXCE     HAND_BASE|0x0009
#define     CREAT_CONTA_EXCE    HAND_BASE|0x0011
#define     EINVO_OBJE_EXCE     HAND_BASE|0x0013
#define     FIND_OBJE_EXCE      HAND_BASE|0x0015
#define     INSER_OBJE_EXCE     HAND_BASE|0x0017
#define     UPDAT_OBJE_EXCE     HAND_BASE|0x0019
#define     RELOA_CLAS_OK       HAND_BASE|0x0021
#define     RELOA_CLAS_EXCE     HAND_BASE|0x0023
#define     CLAS_INTEG_EXCE     HAND_BASE|0x0025
#define     CLAS_INTEG_OK       HAND_BASE|0x0027
#define     CLAS_INFO_EXCE      HAND_BASE|0x0029
#define     DROP_CLAS_OK        HAND_BASE|0x0031
#define     DROP_CLAS_EXCE      HAND_BASE|0x0033
#define     CREAT_CLAS_OK       HAND_BASE|0x0035
#define     COMP_CLAS_EXCE      HAND_BASE|0x0037  
#define     CREAT_CLAS_EXCE     HAND_BASE|0x0039    
#define     CLAS_NOT_FOUND      HAND_BASE|0x0041    
#define     RELOA_METH_OK       HAND_BASE|0x0043  
#define     RELOA_METH_EXCE     HAND_BASE|0x0045    
#define     DROP_METH_OK        HAND_BASE|0x0047
#define     DROP_METH_EXCE      HAND_BASE|0x0049    
// #define     DROP_METH_EXCE   HAND_BASE|0x0051    
#define     CREAT_METH_OK       HAND_BASE|0x0053   
#define     COMP_METH_EXCE      HAND_BASE|0x0055    
#define     CREAT_METH_EXCE     HAND_BASE|0x0057    
#define     METH_NOT_FOUND      HAND_BASE|0x0059
#define     QUER_OSTAT_EXCE     HAND_BASE|0x0061 
#define     CLOSE_ODB_OK        HAND_BASE|0x0063  
#define     CLOSE_ODB_EXCE      HAND_BASE|0x0065  
#define     OPEN_ODB_OK         HAND_BASE|0x0067  
#define     OPEN_ODB_EXCE       HAND_BASE|0x0069  
#define     SHOW_ODB_EXCE       HAND_BASE|0x0071  
#define     QUER_ASTAT_EXCE     HAND_BASE|0x0073  
#define     SHOW_AODB_EXCE      HAND_BASE|0x0075
#define     CREAT_INHER_EXCE    HAND_BASE|0x0077

    //
#define     RIVE_BASE      0x00050000


#ifdef __cplusplus
}
#endif

#endif /* EXCEP_CODE_H */

