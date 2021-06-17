
/* 
 * File:   main.c
 * Author: James
 *
 * Created on 2018年10月11日, 下午1:35
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <wiredtiger.h>
#include <wiredtiger_ext.h>

//
#pragma pack(1)

typedef struct {
    int oid;
    uint8_t role_type; // 0x00:osev 0x01:data
    char role_name[32];
    char priv_array[1024];
} role_privi;

#pragma pack()

//

void bind_role(WT_CURSOR *curso, role_privi *obje_data) {
    curso->set_key(curso, obje_data->oid);
    curso->set_value(curso, obje_data->role_type, obje_data->role_name, obje_data->priv_array);
}

void solve_role(role_privi *obje_data, WT_CURSOR *curso) {
    curso->get_key(curso, &(obje_data->oid));
    curso->get_value(curso, &obje_data->role_type, obje_data->role_name, obje_data->priv_array);
}

//

/*
 * 
 */
int xmain(int argc, char** argv) {
    //
    WT_CONNECTION *conn;
    WT_SESSION *session;
    WT_CURSOR *cursor;

    char *home = "./";

    /* Open a connection to the database, creating it if necessary. */
    wiredtiger_open(home, NULL, "create", &conn);

    /* Open a session for the current thread's work. */
    conn->open_session(conn, NULL, NULL, &session);

    /* Do some work... */
    session->create(session, "table:map", "key_format=i,value_format=B32s1024s,columns=(stoid,role_type,role_name,priv_array)");
    session->open_cursor(session, "table:map", NULL, NULL, &cursor);
    // forma_types:key_format=S,value_format=1s32s1024s,columns=(stoid,role_type,role_name,priv_array)
    role_privi role_dat;
    role_dat.oid = 3;
    role_dat.role_type = 0x01;
    strcpy(role_dat.role_name, "david");
    strcpy(role_dat.priv_array, "123456789");
    bind_role(cursor, &role_dat);
    if (0x00 != cursor->insert(cursor)) {
        printf("bind_role\n");
        return -1;
    }
    //
    role_privi role_out;
    cursor->set_key(cursor, 3);
    if (0x00 != cursor->search(cursor)) {
        printf("solve_role\n");
        return -1;
    }
    solve_role(&role_out, cursor);
    printf("sizeof(char *):%d\n", sizeof(char *));
    printf("oid:|%d|\n", role_out.oid);
    printf("role_type:|%u|\n", role_out.role_type);
    // printf("role_name:|%s|\n", *role_out.role_name);
    //char *p = ((char *[])role_out.priv_array)[0x00];
    // printf("priv_array:|%s|\n", p);
    printf("priv_array:|%s|\n", ((char *)role_out.priv_array)[0x00]);

    //
    cursor->close(cursor);
    /* Note: closing the connection implicitly closes open session(s). */
    conn->close(conn, NULL);
    //
    return (EXIT_SUCCESS);
}

