#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int num, char *str[])
{
    /*
    printf("%d\n", num);
    for(int i = 0; i < num; i++)
        printf("%s\n", str[i]);
        */
    if(num == 1) {
        printf("g++.exe: fatal error: no input files\n");
        printf("compilation terminated.\n");
        return 0;
    }
    char cmd[128] = "origin_g++ -fexec-charset=gbk ";
    strcpy(cmd+30, str[1]);
    int len = strlen(cmd);
    if(num == 2) {
        strcpy(cmd+len, " -o tmp.exe");
    } else for(int i = 2; i < num; i++) {
        cmd[len++] = ' ';
        strcpy(cmd+len, str[i]);
        len += strlen(str[i]);
        //printf("%s\n", str[i]);
    }
    //printf("%s\n", cmd);
    system(cmd);
    return 0;     
}
