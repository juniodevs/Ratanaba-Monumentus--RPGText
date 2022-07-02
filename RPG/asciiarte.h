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


void ASCIIinimigo() //TEMPLATE PARA ASCII
{
    
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("                         ~O");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("                       /~()-{---");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);printf("     ---}-()~/\n");
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("                        /~)");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);printf("               (~.\n");
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("                        ~ ~");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);printf("               ~ ~\n");
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
} //FIM ASCII INIMIGO




#endif //SEMPRE NO FINAL DO ARQUIVO