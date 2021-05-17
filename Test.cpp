#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996);

typedef struct People {
    char Name[50];
    char PhoneNumber[50];
    char Address[50];
    int key_name;
    int key_tel;
    int judge;
} People;
typedef People *PPeople;

typedef struct dire_Page *Pdirepage;
typedef struct dire_Page {
    Pdirepage link;
    People s[2];
    int PageNodeSize;//  每一个页块储存元素的大小
} DirePage;

typedef struct BucketNode {
    Pdirepage link;
} BucketNode;
typedef struct dire_Bucket {
    BucketNode *BucketLink;
    int m;
} Bucket;
typedef Bucket *Pbucket;


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

void init_People(PPeople p, PPeople t) {    //在页块中进行赋值
    strcpy(p->Name, t->Name);
    strcpy(p->PhoneNumber, t->PhoneNumber);
    strcpy(p->Address, t->Address);
    p->key_name = t->key_name;
    p->key_tel = t->key_tel;
    p->judge = 1;
}

void init_People(PPeople p, char Name[], char PhoneNumber[], char Address[]) {
    strcpy(p->Name, Name);
    strcpy(p->PhoneNumber, PhoneNumber);
    strcpy(p->Address, Address);
    init_Key(p);
    p->judge = 1;
}

int equalPeople(PPeople p1, PPeople p2) {
    if (strcmp(p1->Name, p2->Name) == 0 && strcmp(p1->PhoneNumber, p2->PhoneNumber) == 0 &&
        strcmp(p1->Address, p2->Address) == 0) {
        return 1;
    } else {
        return 0;
    }
}

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

int hash(int key, int map) {   //哈希函数
    int h = 0;
    h = key % map;
    return h;

}

int search(Pbucket p, PPeople q, int tag, Pdirepage *address, int *Position) {
    Pdirepage t = NULL;
    int key = 0;
    *Position = -1;
    if (tag == 0) {                         // tag = 0 代表通过名字散列表查找
        key = q->key_name;
    } else if (tag == 1) {
        key = q->key_tel;                 //tag 为其它状态代表通过电话查找
    } else {
        printf("Error tag");
        return 0;
    }
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

void Print(Pbucket b, PPeople t, int tag) {
    init_Key(t);
    Pdirepage address = NULL;
    int position = -1;
    int i = 0;
    int tag1 = search(b, t, tag, &address, &position);
    if (tag1 == 0) {
        printf("not exist!\n");
        return;
    }
    printf("Name:%s\n", address->s[i].Name);
    printf("PhoneNumber::%s\n", address->s[i].PhoneNumber);
    printf("Address:%s\n", address->s[i].Address);
}


void enlarge_Bucket(Pbucket& p, int tag) {
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
                if (hash(q->s[k].key_name, m2) > p->m) {
                    tmp = q->s[k];
                    del_Page(p, &q->s[k], tag);
                    insert_Page(NewBucket, &tmp, tag);
                }
            }
            q = q->link;
        }
        p->BucketLink[i].link = NULL;
    }
    free(p);
    p = NewBucket;
}
void Saveinfile(Pbucket p) { //将添加的联系人信息保存至文件里
    int i;
    char x[] = ";", y[] = ";\n";
    char Name[] = "Name:";
    char PhoneNumber[] = "PhoneNumber:";
    char Address[] = "Address:";
    FILE *fg = fopen("TeleBook.txt", "w+");
    if (fg == NULL) {
        perror("error");
        exit(-1);
    }
    for (i = 0; i < p->m; i++) {
        Pdirepage n = p->BucketLink[i].link;
        if (n == NULL) {
            continue;
        }
        while (n != NULL) {
            fflush(stdout);
            for (int j = 0; j < n->PageNodeSize; j++) {
                if (n->s[j].judge == 1) {
                    fflush(stdout);
                    fprintf(fg, "%s%s", n->s[j].Name, x);
                    fprintf(fg, "%s%s", n->s[j].PhoneNumber, x);
                    fprintf(fg, "%s%s", n->s[j].Address, y);
                }
            }
            n = n->link;
        }
    }
    fclose(fg);
}

void ReadFile(Pbucket b1, Pbucket b2) {
    char read[150] = {0};
    People s = {{0}, {0}, {0}, -1, -1, 1};
    FILE *fg = fopen("TeleBook.txt", "r+");
    if (fg == NULL) {
        printf("NO File");
    }
    char *token = NULL;
    char Name[50]{0};
    char PhoneNumber[50]{0};
    char Address[50]{0};
    char flag[2]{";"};
    while ((fscanf(fg, "%s", read)) != EOF) {
        strcpy(s.Name, strtok(read, flag));
        strcpy(s.PhoneNumber, strtok(NULL, flag));
        strcpy(s.Address, strtok(NULL, flag));
        printf("Name:%s\n", s.Name);
        printf("PhoneNumber:%s\n", s.PhoneNumber);
        printf("Address:%s\n", s.Address);
        insert_Page(b1, &s, 0);
        insert_Page(b2, &s, 1);
//       printf("tel:%s",b2->BucketLink[4],)
    }

}

int main() {
    int tag = 0;
    int tag1 = 0;
    People p;
    int m = 20;
    int num = 0;
    Pbucket b1 = create_Bucket(m);
    Pbucket b2 = create_Bucket(m);
    FILE *book = fopen("TeleBook.txt", "r+");
    if (book != NULL) {
        ReadFile(b1, b2);
        printf("已存在电话簿文件，成功读取!\n");
        fflush(stdout);
    }
    out:
    printf("1.增添记录\n");
    printf("2.删除记录\n");
    printf("3.以电话号码进行查找\n");
    printf("4.以姓名进行查找\n");
    printf("5.退出\n");
    fflush(stdout);
    scanf("%d", &tag);
    if (tag == 1) {
        printf("输入姓名：");
        fflush(stdout);
        scanf("%s", p.Name);
        printf("输入电话号码：");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        printf("输入地址：");
        fflush(stdout);
        scanf("%s", p.Address);
        insert_Page(b1, &p, 0);
        insert_Page(b2, &p, 1);
        num++;
        if (num >= 10) {
            enlarge_Bucket(b1, 0);
            enlarge_Bucket(b2, 1);
        }
        goto out;
    } else if (tag == 2) {
        printf("1.以电话号码进行删除\n");
        printf("2.以姓名进行删除\n");
        fflush(stdout);
        scanf("%d", &tag1);
        if (tag1 == 1) {
            printf("输入电话号码：");
            fflush(stdout);
            scanf("%s", p.PhoneNumber);
            del_Page(b2, &p, 1);
        } else if (tag1 == 2) {
            printf("输入姓名：");
            fflush(stdout);
            scanf("%s", p.Name);
            del_Page(b1, &p, 0);
        }
    } else if (tag == 3) {
        enlarge_Bucket(b1,0);
        printf("\nb1:%d\n",b1->m);
        goto out;
    } else if (tag == 4) {
        printf("输入姓名：");
        fflush(stdout);
        scanf("%s", p.Name);
        Print(b1, &p, 0);
        goto out;
    } else if (tag == 5) {
        Saveinfile(b1);
        return 0;
    } else {
        printf("error\n");
        getchar();
        fflush(stdout);
        goto out;
    }
    return 0;
}
