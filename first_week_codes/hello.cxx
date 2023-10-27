#include <stdio.h>

int c = 8;
int b;
int topla (int,int);
extern char etext, edata, end;

int main(){
    int   a=3;
    bool  d=false;
    char  e='A';
    int   f=66;
    int   g=67;
    float h=3.12;
  
    printf("a değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&a,sizeof(a));
    printf("d değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&d,sizeof(d));
    printf("e değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&e,sizeof(e));
    printf("f değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&f,sizeof(f));
    printf("g değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&g,sizeof(g));
    printf("h değişkenin adresi : %p \t kapladigi alan : %lu byte \n",&h,sizeof(h));

    printf("Adress of Txt Seg function: %p\t Occupied Area : %lu byte \n",&etext,sizeof(etext));
    printf("Adress of eData Seg function: %p\t Occupied Area : %lu byte \n",&edata,sizeof(edata));
    printf("Adress of end Seg function: %p\t Occupied Area : %lu byte \n",&end,sizeof(end));
    printf("Adress of Main function: %p\n", main);
    printf("Adress of Topla function: %p\n", topla);
    printf("Adress of Global c int: %p\t Occupied Area : %lu byte \n",&c,sizeof(c));
    printf("Adress of Global b int: %p\t Occupied Area : %lu byte \n",&b,sizeof(b));
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

