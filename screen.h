/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   screen.h
 * Author: alram
 *
 * Created on September 30, 2019, 5:06 PM
 */

#ifndef SCREEN_H
#define SCREEN_H




#include <stdio.h>

#define SCREEN_NC 120 //estos dos deberian poder cambiarse facilmente para modificar el tamano
#define SCREEN_NR 28

#define  N_COLORS 16
#define  I_NRM  0
#define  I_RED  1
#define  I_GRN  2
#define  I_YEL  3
#define  I_BLU  4
#define  I_MAG  5
#define  I_CYN  6
#define  I_WHT  7



void gotoxy(int x,int y);
void clearScreen(void);
void setColor(int idxColor);





#endif /* SCREEN_H */

