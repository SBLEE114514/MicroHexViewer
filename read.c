#include <stdlib.h>
#include <string.h>
#include "read.h"

BYTE buffer[BUFFER_SIZE<<1];
int cnt;
unsigned int size=0;

int min(int x,int y){
    return x<y?x:y;
}

char* to_str(int x){
    static int sta[10],tp;
    tp=0;
    char* res=malloc(10);
    if(x==0){
        sta[tp++]=0;
    }
    while(x>0){
        sta[tp++]=x%10;
        x/=10;
    }
    int cnt=0;
    while(tp>0){
        res[cnt++]=sta[--tp]+48;
    }
    res[cnt]=0;
    return res;
}

char* concat(const char* s1,const char* s2){
    int n=strlen(s1);
    int m=strlen(s2);
    char* res=malloc(n+m+1);
    memcpy(res,s1,n);
    memcpy(res+n,s2,m);
    res[n+m]=0;
    return res;
}
int init(const char* filename){
    int sz=0;
    FILE* fp=fopen(filename,"rb");
    if(fp==NULL){
        fputs("failed",stderr);
        return 1;
    }
    while((sz=fread(buffer,1,BUFFER_SIZE,fp))>0){
        size+=sz;
        FILE* outfile;
        char* str=concat("./tmp/file",to_str(cnt++));
        if((outfile=fopen(str,"wb"))==NULL){
            fputs("tmp file creating failed",stderr);
            fclose(fp);
            exit(1);
        }
        fwrite(buffer,1,sz,outfile);
        fclose(outfile);
        if(cnt*BUFFER_SIZE>MAXBYTES){
            fputs("file size out of limitation!",stderr);
            fclose(fp);
            exit(1);
        }
    }
    fclose(fp);
    return cnt;
}

BYTE* get(unsigned int addr,unsigned int *n){
    unsigned int blo=addr>>12;
    unsigned int idx=addr&4095;
    FILE* fp;
    if((fp=fopen(concat("./tmp/file",to_str(blo)),"rb"))==NULL){
        fputs("failed!",stderr);
        fclose(fp);
        exit(1);
    }
    fread(buffer,1,BUFFER_SIZE,fp);
    if(idx+*n>=4096&&blo+1<cnt){
        if((fp=fopen(concat("./tmp/file",to_str(blo+1)),"rb"))==NULL){
            fputs("failed!",stderr);
            fclose(fp);
            exit(1);
        }
        *n=min(4096,4096-idx+16+fread(buffer+BUFFER_SIZE,1,BUFFER_SIZE,fp));
    }
    fclose(fp);
    return buffer+idx;
}