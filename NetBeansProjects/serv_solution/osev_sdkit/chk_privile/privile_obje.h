
/* 
 * File:   privile_obje.h
 * Author: James Xu
 *
 * Created on 2017.1.4, AM 9:33
 */

#ifndef PRIVILE_OBJE_H
#define PRIVILE_OBJE_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif
    //
#define INVA_PRIV       0x00000000

    // general scope
#define SCOP_OSEV       0x01000000
#define SCOP_OSDB       0x02000000 // osdb level
#define SCOP_EOBJ       0x04000000
#define PRIVI_SCOPE(PRIMK)    (PRIMK & 0xFFFF0000)
    // SCOP_OSDB sub scope
#define LEVE_ONE            0x00010000
#define LEVE_TWOP           0x00020000
#define LEVE_THRE           0x00040000
#define LEVE_FOUP           0x00080000
#define OSDB_LEVE_OTTF (LEVE_ONE | LEVE_TWOP | LEVE_THRE | LEVE_FOUP)
#define CLEAR_SLEVE(PRIMK)    (PRIMK & 0xFF00FFFF)
    //
    // general privile
#define PRIVI_VALUE(PRIMK)    (PRIMK & 0x0000FFFF)
    // SCOP_OSEV privile
#define SVOD_PRIVI      0x00000100 // role / user
#define SVOD_ODBM       0x00000200 // manage the odb
#define SVOD_CLUST      0x00000400 // clust
#define CLEAR_OBSV(PRIMK)    (PRIMK & 0xFFFF00FF)
    // SCOP_OSDB LEVEL privile
#define ODLE_READ       0x00000001
#define ODLE_WRITE      0x00000002
#define ODLE_EXECU      0x00000004
#define CLEAR_ODLE(PRIMK)    (PRIMK & 0xFFFFFF00)
    // SCOP_EOBJ privile
#define COEN_ECHO       0x00000001
#define COEN_CREAT      0x00000002
#define COEN_DROP       0x00000004
#define COEN_FIND       0x00000008
#define COEN_UPDAT      0x00000010
#define COEN_INSER      0x00000020
#define COEN_FACTO      0x00000040
#define COEN_INVOK      0x00000080
#define CLEAR_COEN(PRIMK)    (PRIMK & 0xFFFF0000)
    //
    extern uint32 minvo_privi[];
    extern uint32 cinvo_privi[];
    //

    typedef struct {
        uint32 ole_pmk;
        uint32 coq_pmk;
    } coqu_pvmk;

    extern coqu_pvmk const_privi[];
    extern coqu_pvmk query_privi[];


#ifdef __cplusplus
}
#endif

#endif /* PRIVILE_OBJE_H */

