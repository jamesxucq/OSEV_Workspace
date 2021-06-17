
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

#define OID_BINARY_LEN      12
#define OID_LINE_LEN        25

//
#pragma pack(1)

typedef struct {
    unsigned int osev_unique; // machine_unique
    unsigned long long stoid;
} osv_oid_i;
#pragma pack()

#pragma pack(1)

typedef struct {
    unsigned int osev_unique; // machine_unique
    unsigned int time_stamp;
    unsigned int counter;
} osv_oid_t;
#pragma pack()

//

char *oidstr(char *oid_stri, osv_oid_t *obje_oid) {
    char *toksp = oid_stri;
    char *tokst = (char *) obje_oid;
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) tokst[0x00]);
        toksp += 0x02;
        tokst++;
    }
    oid_stri[24] = '\0';
    return oid_stri;
}

/*
 * 
 */
int main(int argc, char** argv) {
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
    session->create(session, "table:map", "key_format=r,value_format=i,columns=(stoid,role_type)");
    session->open_cursor(session, "table:map", NULL, NULL, &cursor);
    // forma_types:key_format=S,value_format=1s32s1024s,columns=(stoid,role_type,role_name,priv_array)
    osv_oid_i oid;
    oid.stoid = 14433338261;
    char oid_stri[OID_LINE_LEN];
    // oidstr(oid_stri, (osv_oid_t *) & oid);
    // printf("oid_stri:%s\n", oid_stri);

    //
    unsigned long long rkey;
    cursor->set_key(cursor, oid.stoid);
    cursor->get_key(cursor, &rkey);
    printf("--- rkey:%llu\n", rkey);
    cursor->set_value(cursor, 1);
    cursor->insert(cursor);
    oid.stoid = 345;
    cursor->set_key(cursor, oid.stoid);
    cursor->get_key(cursor, &rkey);
    printf("--- rkey:%llu\n", rkey);
    cursor->set_value(cursor, 2);
    cursor->insert(cursor);
    //
    int value;
    cursor->set_key(cursor, oid.stoid);
    int ret = cursor->search(cursor);
    printf("ret:%d\n", ret);
    cursor->get_value(cursor, &value);
    printf("value:%d\n", value);
    //
    cursor->close(cursor);
    /* Note: closing the connection implicitly closes open session(s). */
    conn->close(conn, NULL);
    
    printf("unsigned long long:%d\n", sizeof(unsigned long long));
    //
    return (EXIT_SUCCESS);
}

