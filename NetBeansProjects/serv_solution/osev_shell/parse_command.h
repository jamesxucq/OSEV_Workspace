
#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "stri_utili.h"

    // clie must handle, general is server handle, comd_clie local handle

    typedef enum {
        comd_inval,
        comd_conne, // client conne
        comd_exit, // client exit
        comd_bye, // client bye
        comd_clie, // general
        comd_use, // client use
        comd_quit, // client quit
        comd_stat, // general
        comd_priv, // general
        comd_mana, // general
        comd_level, // client level 
        comd_leve, // general
    } command;

#define ATTRI_INVALID      0x00
#define ATTRI_MAJOR        0x00000001
#define ATTRI_EXTEND       0x00000002
    //

    typedef enum {
        come_inval,
        come_list,
        come_load,
        come_save,
        come_conv,
        come_pret
    } extend_comd;

    //

    typedef struct {
        char coline[LARGE_TEXT_SIZE];
        unsigned int comd_attrib; //
        unsigned int comd_valu;
        char obje_iden[OBJE_LENGTH];
        char comd_meth[METH_LENGTH];
        unsigned int meth_valu;
        //
        char paras_line[LARGE_TEXT_SIZE];
        char *paras[PARAM_NUMB];
        int reserved;
    } osev_command;

    char *parse_command(osev_command *oscmd, uint32 shell_mode, uint32 run_level);

    //
    int valid_command_type(char *comd_line, char *cline_stri);
    char *parse_extend(osev_command *oscmd, uint32 shell_mode, uint32 run_level);

    //

    enum statu_meth {
        stat_inval,
        stat_echo,
        stat_open, // start create
        stat_close, // shutdown
        stat_status,
        stat_stati
    };

    enum privi_meth {
        priv_inval,
        priv_list,
        priv_role,
        priv_user
    };

    enum invok_meth {
        invo_inval,
        invo_list,
        invo_creat,
        invo_drop,
        invo_repla,
        invo_integri,
        invo_reload
    };

    enum colle_meth {
        coll_inval,
        coll_list,
        coll_creat,
        coll_drop,
        coll_repla,
        coll_integri,
        coll_reload
    };
    
    enum const_meth {
        cons_inval,
        cons_echo,
        cons_creat,
        cons_drop,
        cons_updat,
        cons_inser,
        cons_find,
        cons_invok
    };

    enum query_meth {
        quer_inval,
        quer_echo,
        quer_creat,
        quer_drop,
        quer_updat,
        quer_inser,
        quer_find,
        quer_invok,
        quer_facto
    };


#ifdef __cplusplus
}
#endif

#endif /* PARSE_COMMAND_H */

