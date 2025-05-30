main.exe:main.o read.o CUI.o
	gcc main.o read.o CUI.o -o main.exe -Os -s -flto -static
main.o:main.c read.h CUI.h
	gcc main.c -c -Os -s -flto -static
read.o:read.c read.h
	gcc read.c -c -Os -s -flto -static
CUI.o:CUI.c CUI.h
	gcc CUI.c -c -Os -s -flto -static