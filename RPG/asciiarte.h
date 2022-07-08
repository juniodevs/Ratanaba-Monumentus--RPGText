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
    case 4: //verde
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        break;
    case 5: //amarelo
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        break;
    case 6: //cinza
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        break;
    case 7: //preto
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        break;
    case 8: //rosa
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        break;
    case 9: //ciano
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        break;
    case 10: //roxo
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        break;
    case 11: //marrom
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        break;
    default: //default
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;

    }

    // cor(1); //vermelho
    // cor(2); //azul
    // cor(3); //branco
}

void piscartela()
{
    system("color 7");
    delay(100);
    system("color 0");
}


void ASCIIinimigo() //TEMPLATE PARA ASCII
{
    
cor(1); printf("                         ~O");cor(2);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("     ---}-()~/\n");
cor(1); printf("                        /~)");cor(2);printf("               (~.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ~ ~\n");
cor(3);
} //FIM ASCII INIMIGO

void pocao() //TEMPLATE PARA POÇÃO
{
cor(1);
printf("     |-|\n");
printf("     | |   \n");
printf("   __| |__  Você regenerou\n");
printf("  :       :    sua vida!\n");
printf("  :#######:\n");    
printf("  ;#######;\n");
cor(3);

Dialogo("Você regenerou sua vida!", 0);
} //FIM ASCCI POÇÃO

#endif //SEMPRE NO FINAL DO ARQUIVO