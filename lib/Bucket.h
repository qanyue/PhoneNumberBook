//
// Created by qanyu on 2021/5/9 0009.
//



#ifndef LIBRARY_BUCKET_H
#define LIBRARY_BUCKET_H

#include "stdio.h"
#include "People.h"
#include "stdlib.h"

typedef struct dire_Page {
    struct dire_Page* link;
    People s[2];
    int PageNodeSize;//  每一个页块储存元素的大小
} DirePage;
typedef DirePage *Pdirepage;

typedef struct BucketNode {
    Pdirepage link;
} BucketNode;

typedef struct dire_Bucket {
    BucketNode *BucketLink;
    int m;
} Bucket;
typedef Bucket * Pbucket;
Pbucket create_Bucket(int m);
void Del_Bucket(Pbucket p);
void enlarge_Bucket(Pbucket& p, int tag);


#endif //LIBRARY_BUCKET_H
