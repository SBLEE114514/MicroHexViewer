#include <stdio.h>
typedef unsigned char BYTE;
#define BUFFER_SIZE 4096
#define MAXBYTES (1024*1024)
extern BYTE buffer[];
int init(const char* filename);
BYTE* get(unsigned addr,unsigned int *n);
extern unsigned int size;
void clear();