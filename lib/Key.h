//
// Created by qanyu on 2021/5/9 0009.
//

#ifndef TELEBOOK_KEY_H
#define TELEBOOK_KEY_H
#include "People.h"
#include "Bucket.h"
void init_Key(PPeople t);
int hash(int key, int map);
int search(Pbucket p, PPeople q, int tag, Pdirepage *address, int *Position);
void Print(Pbucket b, PPeople t, int tag);
#endif //TELEBOOK_KEY_H
