//
// Created by qanyu on 2021/5/9 0009.
//
#include <Dire_Page.h>
#include "../lib/IOFile.h"
void Saveinfile(Pbucket p) { //将添加的联系人信息保存至文件里
    int i;
    char x[] = ";", y[] = ";\n";
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
            for (int j = 0; j < n->PageNodeSize; j++) {
                if (n->s[j].judge == 1) {
                    fprintf(fg, "%s%s", n->s[j].Name, x);
                    fprintf(fg, "%s%s", n->s[j].PhoneNumber, x);
                    fprintf(fg, "%s%s", n->s[j].Address, y);
                    fflush(stdout);
                }
            }
            n = n->link;
        }
    }
    fclose(fg);
}

void ReadFile(Pbucket b1,int &num) {
    char read[150] = {0};
    People s = {{0}, {0}, {0},  -1, 1};
    FILE *fg = fopen("TeleBook.txt", "r+");
    if (fg == NULL) {
        printf("NO File!\n");
        fflush(stdout);
        return;
    }

    char flag[2]{";"};
    while (fscanf(fg, "%s", read) != EOF) {
        strcpy(s.Name, strtok(read, flag));
        strcpy(s.PhoneNumber, strtok(NULL, flag));
        strcpy(s.Address, strtok(NULL, flag));
        insert_Page(b1, &s);
        num++;
        if (num >= b1->m / 2) {
            enlarge_Bucket(b1);
        }
    }
}
