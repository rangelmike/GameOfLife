// EN WINDOWS
// #include <windows.h>
//Define extra colours
#define FOREGROUND_WHITE        (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)   //7
#define FOREGROUND_YELLOW           (FOREGROUND_RED | FOREGROUND_GREEN)                 //3
#define FOREGROUND_CYAN             (FOREGROUND_BLUE | FOREGROUND_GREEN)                //6
#define FOREGROUND_MAGENTA          (FOREGROUND_RED | FOREGROUND_BLUE)                  //5
#define FOREGROUND_BLACK        0                                                       //0

#define FOREGROUND_INTENSE_BLUE     (FOREGROUND_BLUE | FOREGROUND_INTENSITY)            //8
#define FOREGROUND_INTENSE_CYAN     (FOREGROUND_CYAN | FOREGROUND_INTENSITY)            //9
#define FOREGROUND_INTENSE_GREEN    (FOREGROUND_GREEN | FOREGROUND_INTENSITY)           //10
#define FOREGROUND_INTENSE_MAGENTA  (FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)         //11
#define FOREGROUND_INTENSE_RED      (FOREGROUND_RED | FOREGROUND_INTENSITY)             //12
#define FOREGROUND_INTENSE_WHITE    (FOREGROUND_WHITE | FOREGROUND_INTENSITY)           //13
#define FOREGROUND_INTENSE_YELLOW   (FOREGROUND_YELLOW | FOREGROUND_INTENSITY)          //14
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "screen.h"


// USAR ESTA FUNCION EN WINDOWS
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) // en windows
{
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// USAR ESTA FUNCION EN LINUX/MAC
// void gotoxy(int x,int y){
//    printf("%c[%d;%df",0x1B,y,x);
// }


// ESTA SIRVE EN CUALQUIER SISTEMA LINUX/WINDOWS/MAC
void clearScreen(void){

    for(int r=0;r<SCREEN_NR;r++)
        for(int c=0;c<SCREEN_NC;c++){
            gotoxy(c,r);
            printf(" ");
        }
}

//WINDOWS
// void setColor(int idxColor){
//     idxColor%=N_COLORS;
//     WORD colores[] = {FOREGROUND_BLACK, FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_YELLOW, FOREGROUND_BLUE, FOREGROUND_MAGENTA, FOREGROUND_CYAN, FOREGROUND_WHITE, FOREGROUND_INTENSE_BLUE, FOREGROUND_INTENSE_CYAN, FOREGROUND_INTENSE_GREEN, FOREGROUND_INTENSE_MAGENTA, FOREGROUND_INTENSE_RED, FOREGROUND_INTENSE_WHITE, FOREGROUND_INTENSE_YELLOW};
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colores[idxColor]);
// }

//LINUX
// void setColor(int idxColor){
//     switch (idxColor) {
//         case I_NRM:
//             printf("\x1B[0m");
//             break;
//         case I_RED:
//             printf("\x1B[31m");
//             break;
//         case I_GRN:
//             printf("\x1B[32m");
//             //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
//             break;
//         case I_YEL:
//             printf("\x1B[33m");
//             //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW);
//             break;
//         case I_BLU:
//             printf("\x1B[34m");
//             break;
//         case I_MAG:
//             printf("\x1B[35m");
//             break;
//         case I_CYN:
//             printf("\x1B[36m");
//             break;
//         case I_WHT:
//             printf("\x1B[37m");
//             break;
//     }

// }


// ejemplo de poner un color

//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW);
