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
typedef People* PPeople;

typedef struct dire_Page *Pdirepage;
typedef struct dire_Page {
    Pdirepage link;
    People s[2];
    int PageNodeSize;//  每一个页块储存元素的大小
}DirePage;

typedef struct BucketNode {
    Pdirepage link;
}BucketNode;
typedef struct dire_Bucket {
    BucketNode *BucketLink;
    int m;
}Bucket;
typedef Bucket * Pbucket;


void init_Key(PPeople t){
    int key_name =0;
    int key_tel =0;
    int i=0;
    for (i = 0; t->Name[i] != '\0'; i++){
        key_name += t->Name[i];
    }
    for (i = 0;t->PhoneNumber[i]!='\0'; i++) {
        key_tel += t->PhoneNumber[i];
    }
    t->key_name = key_name;
    t->key_tel = key_tel;

}

Pbucket init_Bucket(int m){    //创建并初始化散列桶
    Pbucket p = (Pbucket)malloc(sizeof(struct dire_Bucket));
    int i = 0;
    if (p  != NULL) {
        p->BucketLink = (BucketNode*)malloc(sizeof(struct dire_Page) * m);
        for (i = 0; i < 20; i++) {
            p->BucketLink[i].link = NULL;
        }
        p->m = m;
    }
    else {
        printf("Out of space!\n"); //无空间
         return NULL;
    }
    return p;
}
void init_People(PPeople p,PPeople t){    //在页块中进行赋值
    strcpy(p->Name, t->Name);
    strcpy(p->PhoneNumber, t->PhoneNumber);
    strcpy(p->Address, t->Address);
    p->key_name = t->key_name;
    p->key_tel = t->key_tel;
    p->judge = 1;
}
int equalPeople(PPeople p1,PPeople p2){
    if(strcmp(p1->Name,p2->Name)==0&& strcmp(p1->PhoneNumber,p2->PhoneNumber)==0&& strcmp(p1->Address,p2->Address)){
        return 1;
    } else{
        return 0;
    }
}
Pdirepage create_Page() {           //创建页块
    Pdirepage p = (Pdirepage)malloc(sizeof(struct dire_Page));
    if (p == NULL) {
        printf("FAIL");
        return NULL;
    }
    else {
        p->link = NULL;
        for(int i=0;i<2;i++){
            p->s[i].key_name = 0;
            p->s[i].key_tel = 0;
            strcpy(p->link->s[i].Address, "\0");
            strcpy(p->link->s[i].Name, "\0");
            strcpy(p->link->s[i].PhoneNumber, "\0");
            p->s[i].judge = 0;
        }
        p->PageNodeSize = 2;//每个页块储存的元素设为2
        return p;
    }
}

int hash(int key,int map) {   //哈希函数
    int h = 0;
    h = key % map;
    return h;

}

int search(Pbucket p,PPeople q,int tag,Pdirepage address,int* Position){
    Pdirepage  t = NULL;
    int key =  0;
    *Position = -1;
    if(tag == 0){// tag = 0 代表通过名字散列表查找
        key = q->key_name;
    }else if(tag == 1){
        key = q->key_tel;//tag 为其它状态代表通过电话查找
    }else{
        printf("Error tag");
        return 0;
    }
    t = p->BucketLink[hash(key, p->m)].link;
    while(t!=NULL){
        for (int i = 0; i < t->PageNodeSize; ++i) {
            if(equalPeople(q,&t->s[i])){
                *Position = i;
                address = t;
                return 1;
            }
        }
        t = t->link;
    }
    return 0;
}

void  set_Page(Pbucket b1,PPeople t,int h){  //在页块中寻找可以插入的地方
     if (b1->BucketLink[h].link == NULL) {
        Pdirepage p = create_Page();
         init_People(&p->s[0],t);
        b1->BucketLink[h].link=p;
    }else{
        Pdirepage p = b1->BucketLink[h].link;
        while(p->link!=NULL && p->s[0].judge == 1 && p->s[1].judge == 1){
            p=p->link;
        }
        if(p->s[0].judge==0){
            init_People(&p->s[0],t);
        }else if(p->s[1].judge==0){
            init_People(&p->s[1],t);
        }else{
            Pdirepage q = create_Page();
            init_People(&q->s[0],t);
        }

    }
}
void insert_Page_name(PPeople t, Pbucket b1) {  //实现名字散列表插入操作
    Pdirepage address = NULL;
    int position = -1;
    int tag = search(b1,t,0,address,&position);
    if(tag==1){                               //如果tag=0，电话簿中不存在，进行插入，否则返回
        printf("exist!");
        return;
    }
    int i = 0;
    int h1=-1;

    h1 = hash(t->key_name,b1->m);
    set_Page(b1,t,h1);
}
void insert_Page_tel(PPeople t, Pbucket b) {  //实现电话散列表插入操作
    Pdirepage address = NULL;
    int position = -1;
    int tag = search(b,t,1,address,&position);
    if(tag==1){                               //如果tag=0，电话簿中不存在，进行插入，否则返回
        printf("exist!");
        return;
    }
    int i = 0;
    int  h2=-1;
    h2 = hash(t->key_tel,b->m);
    set_Page(b,t,h2);
}
void enlarge_Bucket(Pbucket p,int mode){
    int m2 = 2*p->m;
    int hashkey=-1;
    Pdirepage t = NULL;
    Pdirepage v = NULL;
    Pbucket NewBucket = (Pbucket) malloc(sizeof(Bucket));
    NewBucket->m  = m2;
    NewBucket->BucketLink = (BucketNode *) malloc(sizeof(BucketNode) * m2);
    for(int i= 0;i < p->m;i++) {
        v = p->BucketLink[i].link;
        int j = i;
        NewBucket->BucketLink[j].link = p->BucketLink[i].link;
        t = p->BucketLink[i].link;
        while (t != NULL) {
            for (int k = 0; k < (t->PageNodeSize); k++) {
                if ((hashkey=hash(t->s[k].key_name, p->m)) > p->m) {
                    insert_Page_
                }

            }
        }


    }

}


int main() {
    People p;

    int m = 20;
    Pbucket b1 = init_Bucket(m);
    Pbucket b2 = init_Bucket(m);
    return 0;
}
