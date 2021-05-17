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
        printf("�Ѵ��ڵ绰���ļ����ɹ���ȡ%d��!\n",num);
        fflush(stdout);
    }
    out:
    printf("===========================\n");
    printf("1.�����¼\n");
    printf("2.ɾ����¼\n");
    printf("3.�Ե绰������в���\n");
    printf("4.��ӡȫ��\n");
    printf("5.�˳�\n");
    printf("===========================\n");
    fflush(stdout);
    scanf("%d", &tag);
    getchar();
    printf("===========================\n");
    if (tag == 1) {
        printf("����������");
        fflush(stdout);
        scanf("%s", p.Name);
        printf("����绰���룺");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        printf("�����ַ��");
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
        printf("����绰���룺");
        fflush(stdout);
        scanf("%s", p.PhoneNumber);
        printf("===========================\n");
        del_Page(b, &p);
        goto out;
    } else if (tag == 3) {
        printf("����绰���룺");
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
