//
// Created by qanyu on 2021/5/9 0009.
//

#ifndef LIBRARY_PEOPLE_H
#define LIBRARY_PEOPLE_H
#include "string.h"
typedef struct People {
    char Name[50];
    char PhoneNumber[50];
    char Address[50];
    int key_name;
    int key_tel;
    int judge;
} People;
typedef People *PPeople;

void init_People(PPeople p, PPeople t);
int equalPeople(PPeople p1, PPeople p2);

#endif //LIBRARY_PEOPLE_H