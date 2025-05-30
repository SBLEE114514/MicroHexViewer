#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#include "read.h"
#include "CUI.h"

int main(int argc,char* argv[]){
    if(argc!=2) return 1;
    int blocks=init(argv[1]);
    printf("%d blocks in total\n%u Bytes in total\n",blocks,size);
    char flag,lst=-1;
    int op;
    do{
        printscreen();
        getcmd(&flag,&op);
        if(flag=='E') break;
        if(flag=='.') flag=lst;
        lst=flag;
        if(flag=='G'){
            if(go(op)){
                puts("failed");
            }
        }else if(flag=='U'){
            while(op--)
            if(pageup()){
                puts("failed");
            }
        }else if(flag=='D'){
            if(pagedown()){
                puts("failed");
            }
        }else{
            puts("Unknown");
        }
    }while(1);
}