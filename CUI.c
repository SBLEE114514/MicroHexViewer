#include "CUI.h"
#include "read.h"
#include <ctype.h>
#include <stdio.h>
unsigned int addr=0;
void printscreen(){
    puts("Address    Value                                           Char");
    puts("##########@###############################################@################");
    unsigned int n=MAX_ROWS<<4;
    int pp=0,i;
    for(BYTE* p=get(addr,&n);pp<n;pp+=16){
        printf("0x%.7X.",(addr+pp)>>4);
        for(i=0;i<n&&i<16;++i) printf(" %.2X",*(p+i+pp));
        while(i++<16) printf("   ");
        putchar(' ');
        for(i=0;i<n&&i<16;++i){
            char ch=*(p+i+pp);
            if(!isprint(ch)) ch='.';
            putchar(ch);
        }
        putchar('\n');
    }
}

void getcmd(char* p,int* op){
    static char str[20];
    scanf("%s",str);
    *p=str[0];
    if(*p!='.'&&*p!='E') scanf("%d",op);
}

char pageup(){
    if(addr==0) return 1;
    return addr-=16,0;
}
char pagedown(){
    if((addr^(addr&15))>=size) return 1;
    return addr+=16,0;
}
char go(unsigned int ad){
    if(ad>=size) return 1;
    return addr=ad,0;
}