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
#include "definicaoCores.h"

void erro1(char *fase){
    system("cls");
    printf(C_RED "\n\t !!! CADASTRO %s JÁ REALIZADO !!!\n\n" NONE, fase);
    system("pause");
}

void erro2(char *etapa){
    system("cls");
    printf(C_RED "\n\t !!! FAÇA O CADASTRO %s E TENTE NOVAMENTE !!!\n\n" NONE, etapa);
    system("pause");
}

void erro3(char *ciclo){
    system("cls");
    printf(C_RED "\n\t !!! A %s AINDA NÃO FOI REALIZADA !!!\n\n" NONE, ciclo);
    system("pause");
}

void erro4(char *fase){
    system("cls");
    printf(C_RED "\n\t !!! %s JÁ FOI REALIZADA !!!\n\n" NONE, fase);
    system("pause");
}

void erro5(char *ciclo){
    system("cls");
    printf(C_RED "\n\t !!! AS %s AINDA NÃO FORAM REALIZADAS !!!\n\n" NONE, ciclo);
    system("pause");
}

void erro6(char *ciclo){
    system("cls");
    printf(C_RED "\n\t !!! AS %s JÁ FORAM REALIZADAS !!!\n\n" NONE, ciclo);
    system("pause");
}