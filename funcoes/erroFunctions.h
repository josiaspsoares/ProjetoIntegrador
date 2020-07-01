#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif

void erro1(char *fase){
    system("cls");
    printf( "\n\t !!! CADASTRO %s J� REALIZADO !!!\n\n" , fase);
    system("pause");
}

void erro2(char *etapa){
    system("cls");
    printf( "\n\t !!! FA�A O CADASTRO %s E TENTE NOVAMENTE !!!\n\n" , etapa);
    system("pause");
}

void erro3(char *ciclo){
    system("cls");
    printf( "\n\t !!! A %s AINDA N�O FOI REALIZADA !!!\n\n" , ciclo);
    system("pause");
}

void erro4(char *fase){
    system("cls");
    printf( "\n\t !!! %s J� FOI REALIZADA !!!\n\n" , fase);
    system("pause");
}

void erro5(char *ciclo){
    system("cls");
    printf( "\n\t !!! AS %s AINDA N�O FORAM REALIZADAS !!!\n\n" , ciclo);
    system("pause");
}

void erro6(char *ciclo){
    system("cls");
    printf( "\n\t !!! AS %s J� FORAM REALIZADAS !!!\n\n" , ciclo);
    system("pause");
}
