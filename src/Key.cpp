//
// Created by qanyu on 2021/5/9 0009.
//
#include <People.h>
#include <Dire_Page.h>
#include "Key.h"

void init_Key(PPeople t) {
    int key_name = 0;
    int key_tel = 0;
    int i = 0;
    for (i = 0; t->Name[i] != '\0'; i++) {
        key_name += t->Name[i];
    }
    for (i = 0; t->PhoneNumber[i] != '\0'; i++) {
        key_tel += t->PhoneNumber[i];
    }
    t->key_name = key_name;
    t->key_tel = key_tel;

}

int hash(int key, int map) {   //哈希函数
    int h = 0;
    h = key % map;
    return h;

}
int search(Pbucket p, PPeople q, Pdirepage *address, int *Position) {
    Pdirepage t = NULL;
    int key = -1;
    *Position = -1;
    key = q->key_tel;                 //tag 为其它状态代表通过电话查找
    if (key < 0) {
        return 0;
    }
    if (p->BucketLink[hash(key, p->m)].link == NULL) {
        return 0;
    }
    t = p->BucketLink[hash(key, p->m)].link;

    while (t != NULL) {
        for (int i = 0; i < t->PageNodeSize; ++i) {
            if (t->s[i].judge == 0) {
                continue;
            }
            if (equalPeople(q, &t->s[i])) {
                *Position = i;
                *address = t;
                return 1;
            }
        }
        t = t->link;
    }
    return 0;
}


void Print(Pbucket b, PPeople t) { //查找并显示给定电话号码的记录
    init_Key(t);
    Pdirepage address = NULL;
    int position = -1;

    int tag = search(b, t,  &address, &position);
    if (tag == 0) {
        printf("not exist!\n");
        return;
    }
    printf("Name:%s\n", address->s[position].Name);
    printf("PhoneNumber:%s\n", address->s[position].PhoneNumber);
    printf("Address:%s\n", address->s[position].Address);
}

