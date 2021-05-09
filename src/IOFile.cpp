//
// Created by qanyu on 2021/5/9 0009.
//
#include <Dire_Page.h>
#include "../lib/IOFile.h"
void Saveinfile(Pbucket p) { //将添加的联系人信息保存至文件里
    int  i;
    char x[] = ";", y[] = ";\n";
    FILE* fg = fopen("TeleBook.txt", "w+");
    if (fg == NULL) {
        perror("error");
        exit(-1);
    }
    Pdirepage v = NULL;
    for (i = 0; i < p -> m; i++) {
        Pdirepage n = p->BucketLink[i].link;
        if (n  == NULL) {
            continue;
        }
        v = n->link;
        while (v != NULL) {
            fwrite(v->s ->Name, 50, 1, fg);
            fwrite(x, 1, 1, fg);
            fwrite(v->s->PhoneNumber, 50, 1, fg);
            fwrite(x, 1, 1, fg);
            fwrite(v->s->Address, 50, 1, fg);
            fwrite(y, 1, 1, fg);
            v = v->link;
        }
    }
    fclose(fg);
}
void ReadFile(Pbucket b1,Pbucket b2){
    char read[150]={0};
    People  s ={{0},{0},{0},-1,-1,1};
    FILE* fg = fopen("TeleBook.txt", "r+");
    if(fg == NULL){
        printf("NO File");
    }
    char *token =NULL;
    char Name[50]{0};
    char PhoneNumber[50]{0};
    char Address[50]{0};
    char flag[2] {";"};
    while((fscanf(fg,"%s",read))!=EOF){
        strcpy(s.Name,strtok(read,flag));
        strcpy(s.PhoneNumber, strtok(NULL,flag));
        strcpy(s.Address, strtok(NULL,flag));
//        printf("Name:%s\n",s.Name);
//        printf("PhoneNumber:%s\n",s.PhoneNumber);
//        printf("Address:%s\n",s.Address);
        insert_Page(b1,&s,0);
        insert_Page(b2,&s,1);
    }
}
