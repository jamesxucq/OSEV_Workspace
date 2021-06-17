
/* 
 * File:   hash_table_ex.h
 * Author: Administrator
 *
 * Created on 2017.9.7
 */

#ifndef HASH_TABLE_EX_H
#define HASH_TABLE_EX_H

#ifdef __cplusplus
extern "C" {
#endif

//
#define create_action(FREE_FUNC, BACKET_SIZE)          action_create(lh_strhash, equal_str, FREE_FUNC, BACKET_SIZE)
    
//
unsigned int lh_strhash(void *src);
int equal_str(void *k1, void *k2);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_EX_H */

