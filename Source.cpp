#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#pragma warning(disable:4996);

typedef struct People {
    char Name[50];
    char PhoneNumber[50];
    char Address[50];
    int key_name;
    int key_tel;
    int judge;
}People;

typedef struct dire_Page *Pdirepage;
typedef struct dire_Page {
    Pdirepage link;
    People s[2];
    int PageNodeSize;//  每一个页块储存元素的大小
}PageDire;

typedef struct BucketNode {
    Pdirepage link;
}BucketNode;
typedef struct dire_Bucket {
    BucketNode *PBucket;
    int m;
}Bucket;
typedef Bucket * Pbucket;

Pbucket init_Bucket(int m){    //创建并初始化散列桶
    Pbucket p = (Pbucket)malloc(sizeof(struct dire_Bucket));
    int i = 0;
    if (p  != NULL) {
        p->PBucket = (BucketNode*)malloc(sizeof(struct dire_Page) * m);
        for (i = 0; i < 20; i++) {
            p->PBucket[i].link = NULL;
        }
        p->m = m;
    }
    else {
        printf("Out of space!\n");
        return NULL;
    }
    return p;
}

Pdirepage create_Page() {           //创建页块
    Pdirepage p = (Pdirepage)malloc(sizeof(struct dire_Page));
    if (p == NULL) {
        printf("FAIL");
        return NULL;
    }
    else {
        p->link = NULL;
        p->s[0].key_name = 0;
        p->s[0].key_tel = 0;
        strcpy(p->link->s[0].Address, "\0");
        p->PageNodeSize = 2;//每个页块储存的元素设为2
        return p;
    }
}
int hash(int key,int map = 20) {   //哈希函数
    int h = 0;
    h = key % map;
    return h;
}
void insert_Page(char *name, char *tel, char *add, Pbucket b1, Pbucket b2) {  //实现插入操作
    int i = 0;
    int h1, h2;
    int key_name, key_tel;
    for (i = 0; name[i] != '\0'; i++) {
        key_name += (int)name[i];
    }
    for (i = 0;tel[i] != '\0'; i++) {
        key_tel += (int)tel[i];
    }
    h1 = hash(key_name);
    h2 = hash(key_tel);
    if (b1->PBucket[h1].link == NULL) {
        Pdirepage p = create_Page();
        if (p == NULL) {
            printf("Out of space!\n");
        }
        else {
            strcpy(p->s[0].Name, name);
            strcpy(p->s[0].PhoneNumber, tel);
            strcpy(p->s[0].Address, add);
            p->s[0].key_name = key_name;
            p->s[0].key_tel = key_tel;
            p->s[0].judge = 1;
        }
    }


    Pdirepage p = create_Page();
    if (p == NULL) {
        printf("Out of space!\n");
    }else {
        strcpy(p->s.name, name);
        strcpy(p->s.tel, tel);
        strcpy(p->s.add, add);
        p->s.key_name = 0;
        p->s.key_tel = 0;


    }
}



void enlarge_Bucket_name(Pbucket p){
    int m2 = 2*p->m;
    Pdirepage t = NULL;
    Pdirepage v = NULL;
    Pbucket NewBucket = (Pbucket) malloc(sizeof(Bucket));
    NewBucket->m  = m2;
    NewBucket->PBucket = (BucketNode *) malloc(sizeof(BucketNode) * m2);
    for(int i= 0;i < p->m;i++){
        v = p->PBucket[i].link;
        int j = i;
        NewBucket->PBucket[j].link = p->PBucket[i].link;
        t = p->PBucket[i].link;
        while(t!=NULL){
            for(int k=0;k<(t->PageNodeSize); k++){
                if(t->s[k].key_name){

                }

            }
        }

    }

}
int main() {
    int m = 20;
    Pbucket b1 = init_Bucket(m);
    Pbucket b2 = init_Bucket(m);
}
