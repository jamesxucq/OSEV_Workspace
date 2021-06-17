int WT_CURSOR::search_near	(	WT_CURSOR * 	cursor,
int * 	exactp 
)		
Return the record matching the key if it exists, or an adjacent record.

An adjacent record is either the smallest record larger than the key or the largest record smaller than the key (in other words, a logically adjacent key).

The key must first be set.

An example of a search for an exact or adjacent match:

    cursor->set_key(cursor, key);
    error_check(cursor->search_near(cursor, &exact));
    if (exact == 0) {
        /* an exact match */
    } else if (exact < 0) {
        /* returned smaller key */
    } else if (exact > 0) {
        /* returned larger key */
    }
An example of a forward scan through the table, where all keys greater than or equal to a specified prefix are included in the scan:

    cursor->set_key(cursor, key);
    error_check(cursor->search_near(cursor, &exact));
    if (exact >= 0) {
        /* include first key returned in the scan */
    }
    while ((ret = cursor->next(cursor)) == 0) {
        /* the rest of the scan */
    }
    scan_end_check(ret == WT_NOTFOUND);
An example of a backward scan through the table, where all keys less than a specified prefix are included in the scan:

    cursor->set_key(cursor, key);
    error_check(cursor->search_near(cursor, &exact));
    if (exact < 0) {
        /* include first key returned in the scan */
    }
    while ((ret = cursor->prev(cursor)) == 0) {
        /* the rest of the scan */
    }
    scan_end_check(ret == WT_NOTFOUND);
On success, the cursor ends positioned at the returned record; to minimize cursor resources, the WT_CURSOR::reset method should be called as soon as the record has been retrieved and the cursor no longer needs that position.

Parameters
cursor	the cursor handle
exactp	the status of the search: 0 if an exact match is found, < 0 if a smaller key is returned, > 0 if a larger key is returned
Returns
zero on success and a non-zero error code on failure. See Error handling for details.
Examples:
ex_call_center.c, and ex_cursor.c.