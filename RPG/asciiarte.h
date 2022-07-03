#ifndef ASCCIART_H
#define ASCCIART_H
#define MAX_BUF 200

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>


void cor(nums)
{
    int numero = nums;

    switch (numero)
    {
    case 1: //vermelho
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        break;

    case 2: //azul
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        break;
    case 3: //branco
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;
    default: //default
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;
    }

    // cor(1); //vermelho
    // cor(2); //azul
    // cor(3); //branco
}


void ASCIIinimigo() //TEMPLATE PARA ASCII
{
    
cor(1); printf("                         ~O");cor(2);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("     ---}-()~/\n");
cor(1); printf("                        /~)");cor(2);printf("               (~.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ~ ~\n");
cor(3);
} //FIM ASCII INIMIGO

#endif //SEMPRE NO FINAL DO ARQUIVO