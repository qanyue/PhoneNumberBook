//
// Created by qanyu on 2021/5/9 0009.
//
#include "../lib/People.h"

void init_People(PPeople p, PPeople t) {    //在页块中进行赋值
    strcpy(p->Name, t->Name);
    strcpy(p->PhoneNumber, t->PhoneNumber);
    strcpy(p->Address, t->Address);
    p->key_tel = t->key_tel;
    p->judge = 1;
}

int equalPeople(PPeople p1, PPeople p2) {
    if (strcmp(p1->Name, p2->Name) == 0 || strcmp(p1->PhoneNumber, p2->PhoneNumber) == 0) {
        return 1;
    } else {
        return 0;
    }

}
