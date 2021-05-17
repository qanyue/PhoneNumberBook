//
// Created by qanyu on 2021/5/9 0009.
//
#include <Dire_Page.h>
#include "../lib/Bucket.h"
#include "../lib/Key.h"
Pbucket create_Bucket(int m) {    //创建并初始化散列桶
    Pbucket p = (Pbucket) malloc(sizeof(struct dire_Bucket));
    int i = 0;
    if (p != NULL) {
        p->BucketLink = (BucketNode *) malloc(sizeof(struct dire_Page) * m);
        for (i = 0; i < m; i++) {
            p->BucketLink[i].link = NULL;
        }
        p->m = m;
    } else {
        printf("Out of space!\n"); //无空间
        return NULL;
    }
    return p;
}

void Del_Bucket(Pbucket p) {
    if (p == NULL) {
        printf("Empty Bucket");
        return;
    }
    BucketNode *q = NULL;
    Pdirepage v = NULL;
    Pdirepage tmp = NULL;
    for (int i = 0; i < p->m; ++i) {
        q = &p->BucketLink[i];
        if(q == NULL){
            continue;
        }
        v = q->link;
        while (v != NULL) {
            tmp = v->link;
            free(v);
            v = tmp;
        }
        free(q);
    }
}

void enlarge_Bucket(Pbucket& p) {
    int m2 = 2 * p->m;
    Pdirepage q = NULL;

    Pbucket NewBucket = create_Bucket(m2);
    People tmp  ;
    for (int i = 0; i < p->m; i++) {
        q = p->BucketLink[i].link;
        if(q == NULL){
            continue;
        }
        NewBucket->BucketLink[i].link = q;
        while (q != NULL) {
            for (int k = 0; k < (q->PageNodeSize); k++) {
                if (hash(q->s[k].key_tel, m2) > p->m) {
                    tmp = q->s[k];
                    del_Page(p, &q->s[k]);
                    insert_Page(NewBucket, &tmp);
                }
            }
            q = q->link;
        }
        p->BucketLink[i].link = NULL;
    }
    free(p);
    p = NewBucket;
}