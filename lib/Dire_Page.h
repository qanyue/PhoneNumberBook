//
// Created by qanyu on 2021/5/9 0009.
//


#ifndef DIRE_PAGE_H
#define DIRE_PAGE_H


#include <People.h>
#include "Bucket.h"


void set_Page(Pbucket b1, PPeople t, int h);
Pdirepage create_Page();
void insert_Page(Pbucket b, PPeople t, int mode);
void del_Page(Pbucket b, PPeople t, int tag);


#endif //TELEBOOKL_DIRE_PAGE_H
