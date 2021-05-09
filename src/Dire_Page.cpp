//
// Created by qanyu on 2021/5/9 0009.
//
#include <Key.h>
#include "../lib/Dire_Page.h"

Pdirepage create_Page() {           //创建页块
    Pdirepage p = (Pdirepage) malloc(sizeof(struct dire_Page));
    if (p == NULL) {
        printf("FAIL");
        return NULL;
    } else {
        p->link = NULL;
        p->PageNodeSize = 2;//每个页块储存的元素设为2
        return p;
    }
}
void set_Page(Pbucket b1, PPeople t, int h) {  //在页块中寻找可以插入的地方
    if (b1->BucketLink[h].link == NULL) {
        Pdirepage p = create_Page();
        init_People(&p->s[0], t);
        b1->BucketLink[h].link = p;
    } else {
        Pdirepage p = b1->BucketLink[h].link;
        while (p->link != NULL && p->s[0].judge == 1 && p->s[1].judge == 1) {
            p = p->link;
        }
        if (p->s[0].judge == 0) {
            init_People(&p->s[0], t);
        } else if (p->s[1].judge == 0) {
            init_People(&p->s[1], t);
        } else {
            Pdirepage q = create_Page();
            init_People(&q->s[0], t);
        }

    }
}

void insert_Page(Pbucket b, PPeople t, int mode) {  //实现名字散列表插入操作
    init_Key(t);
    Pdirepage address = NULL;
    int position = -1;
    int tag = search(b, t, mode, &address, &position);
    if (tag == 1) {                               //如果tag=0，电话簿中不存在，进行插入，否则返回
        printf("exist!\n");
        return;
    }
    if (mode == 0) {
        int h1 = -1;
        h1 = hash(t->key_name, b->m);
        set_Page(b, t, h1);
    } else if (mode == 1) {
        int h2 = -1;
        h2 = hash(t->key_tel, b->m);
        set_Page(b, t, h2);
    }
}

void del_Page(Pbucket b, PPeople t, int tag) {    //实现散列表删除操作
    init_Key(t);
    Pdirepage address = NULL;
    int position = -1;
    int i = 0;
    int tag1 = search(b, t, tag, &address, &position);
    if (tag1 == 0) {
        printf("not exist!\n");
        return;
    }
    address->s[position].judge = 0;
    if (address->s[0].judge == 0 && address->s[1].judge == 0) {             //如果页块中两个存储都为空，删除此页块
        if (address->link == NULL) {
            Pdirepage q = b->BucketLink[hash(t->key_name, b->m)].link;
            if (q == address) {
                b->BucketLink[hash(t->key_name, b->m)].link = NULL;
                free(q);
            } else {
                while (q->link != address) {
                    q = q->link;
                }
                q->link = NULL;
                free(address);
            }
        } else {
            for (i = 0; i < 2; i++) {
                address->s[i].key_name = address->link->s[i].key_name;
                address->s[i].judge = address->link->s[i].judge;
                address->s[i].key_tel = address->link->s[i].key_tel;
                strcpy(address->s[i].PhoneNumber, address->link->s[i].PhoneNumber);
                strcpy(address->s[i].Name, address->link->s[i].Name);
                strcpy(address->s[i].Address, address->link->s[i].Address);
            }
            address->link = address->link->link;
        }
    }
}
