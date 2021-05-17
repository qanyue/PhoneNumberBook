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
    People p;
    int m = 20;
    int num = 0;
    Pbucket b1 = create_Bucket(m);
    Pbucket b2 = create_Bucket(m);
    FILE * book =fopen("TeleBook.txt", "r+");
    if(book!=NULL){
        ReadFile(b,num);
        printf("已存在电话簿文件，成功读取%d个!\n",num);
        fflush(stdout);
    }
    out:
    printf("===========================\n");
    printf("1.增添记录\n");
    printf("2.删除记录\n");
    printf("3.以电话号码进行查找\n");
    printf("4.打印全部\n");
    printf("5.退出\n");
    printf("===========================\n");
    fflush(stdout);
    scanf("%d", &tag);
    getchar();
    printf("===========================\n");
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
        printf("===========================\n");
        insert_Page(b, &p);
        printf("===========================\n");
        num++;
        if(num >=b->m/2){

            enlarge_Bucket(b);
        }
        goto out;
    } else if (tag == 2) {
        printf("输入电话号码：");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        printf("===========================\n");
        del_Page(b, &p);
        goto out;
    } else if (tag == 3) {
        printf("输入电话号码：");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        printf("===========================\n");
        Print(b, &p);
        goto out;
    }  else if(tag==4) {
        Print_All(b);
        goto out;
    }  else if (tag == 5) {
        Saveinfile(b);
        return 0;
    } else {
        printf("===========================\n");
        printf("error\n");
        fflush(stdout);
        goto out;
    }
    return 0;
}
