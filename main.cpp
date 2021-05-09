#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include "lib/Bucket.h"
#include "lib/People.h"
#include "lib/IOFile.h"
#include "lib/Dire_Page.h"
#include "lib/Key.h"


int main() {
    int tag = 0;
    int tag1 = 0;
    People p;
    int m = 20;
    int num = 0;
    Pbucket b1 = create_Bucket(m);
    Pbucket b2 = create_Bucket(m);
    FILE * book =fopen("TeleBook.txt", "r+");
    if(book!=NULL){
        ReadFile(b1,b2);
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
        if(num >=10){
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
        } else {
            printf("error\n");
            fflush(stdout);
        }
        goto out;
    } else if (tag == 3) {
        printf("输入电话号码：");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        Print(b2, &p, 1);
        goto out;
    } else if (tag == 4) {
        printf("输入姓名：");
        fflush(stdout);
        scanf("%s", p.Name);
        Print(b1, &p, 0);
        goto out;
    } else if (tag == 5) {
        return 0;
    } else {
        printf("error\n");
        fflush(stdout);
        goto out;
    }
    return 0;
}
