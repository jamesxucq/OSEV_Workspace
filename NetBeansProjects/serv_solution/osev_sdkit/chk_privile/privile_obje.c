#include "commo_header.h"

#include "privile_obje.h"

//

uint32 minvo_privi[] = {
    LEVE_ONE | ODLE_READ, // echo
    LEVE_ONE | ODLE_WRITE, // creat
    LEVE_ONE | ODLE_WRITE, // repla
    LEVE_ONE | ODLE_WRITE, // drop
    LEVE_ONE | ODLE_EXECU, // integri
    LEVE_ONE | ODLE_EXECU // reload
};

uint32 cinvo_privi[] = {
    LEVE_TWOP | ODLE_READ, // echo
    LEVE_TWOP | ODLE_WRITE, // creat
    LEVE_TWOP | ODLE_WRITE, // repla
    LEVE_TWOP | ODLE_WRITE, // drop
    LEVE_TWOP | ODLE_EXECU, // integri
    LEVE_TWOP | ODLE_EXECU // reload
};

//

coqu_pvmk const_privi[] = {
    {LEVE_THRE | ODLE_READ, SCOP_EOBJ | COEN_ECHO}, // echo
    {LEVE_THRE | ODLE_WRITE, SCOP_EOBJ | COEN_CREAT}, // creat
    {LEVE_THRE | ODLE_WRITE, SCOP_EOBJ | COEN_DROP}, // drop
    {LEVE_THRE | ODLE_WRITE, SCOP_EOBJ | COEN_UPDAT}, // updat
    {LEVE_THRE | ODLE_WRITE, SCOP_EOBJ | COEN_INSER}, // inser
    {LEVE_THRE | ODLE_READ, SCOP_EOBJ | COEN_FIND}, // find
    {LEVE_THRE | ODLE_EXECU, SCOP_EOBJ | COEN_INVOK} // invok
};

coqu_pvmk query_privi[] = {
    {LEVE_FOUP | ODLE_READ, SCOP_EOBJ | COEN_ECHO}, // echo
    {LEVE_FOUP | ODLE_WRITE, SCOP_EOBJ | COEN_CREAT}, // creat
    {LEVE_FOUP | ODLE_WRITE, SCOP_EOBJ | COEN_DROP}, // drop
    {LEVE_FOUP | ODLE_WRITE, SCOP_EOBJ | COEN_UPDAT}, // updat
    {LEVE_FOUP | ODLE_WRITE, SCOP_EOBJ | COEN_INSER}, // inser
    {LEVE_FOUP | ODLE_READ, SCOP_EOBJ | COEN_FIND}, // find
    {LEVE_FOUP | ODLE_EXECU, SCOP_EOBJ | COEN_INVOK}, // invok
    {LEVE_FOUP | ODLE_READ, SCOP_EOBJ | COEN_FACTO} // facto
};
