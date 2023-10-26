#include <stdio.h>

int c = 8;
int b;
int topla (int,int);
extern char etext, edata, end;

int main(){
    int a=3;

    printf("Adress of Txt Seg function: %p\n", &etext);
    printf("Adress of eData Seg function: %p\n", &edata);
    printf("Adress of end Seg function: %p\n", &end);
    printf("Adress of Main function: %p\n", main);
    printf("Adress of Topla function: %p\n", topla);
    printf("Adress of Global c int: %p\n", &c);
    printf("Adress of Global b int: %p\n", &b);
    printf("Adress of Main local a int: %p\n", &a);
    printf("\nToplam = %d: ", topla(a,c));
    return 9;
}

int tola(int x, int y){
    
    static char *buffer;
    buffer= new char[20];
    
    printf("Adress of Topla x int: %p\n", &x);
    printf("Adress of Topla y int: %p\n", &y);
    printf("Adress of Buffer int: %p\n", &buffer);
    printf("Adress of Buffer[3] int: %p\n", &buffer[3]);

    return (x+y);
}

