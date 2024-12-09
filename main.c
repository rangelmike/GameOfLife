#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h" //estructura de datos y manejo de esta
#include "screen.h"     //moverse en la pantalla, cambiar colores, etc
#include "config.h"     //configuracion inicial de la simulacion

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void delay(int cents){
#ifdef _WIN32
    Sleep(cents*10);
#else
    usleep(cents*10*1000);
#endif
}

int validaPos(int x, int y){ //checa que la posicion este dentro de la pantalla
    if(x >= 0 && x < SCREEN_NC)
        if(y>= 0 && y < SCREEN_NR)
            return 1;
    return 0;
}

int setup(char *mapFile, vecCells *vivosAct, int* nVivos){
    FILE *f = fopen(mapFile, "r");
    if(!f) return 0;

    char line[256];
    int ren = 0;
    iVec(vivosAct);
    while(fgets(line, sizeof(line), f)){
        for(int c=0; line[c]; c++){
            if(line[c] == '#'){
                inserta(vivosAct, c, ren);
                *nVivos=*nVivos+1;
            }
        }
        ren++;
    }

    fclose(f);
    return 1;
}

void printMapaIni(vecCells *vivosAct){
    setColor(theme(0,DEAD_CLR));
    for(int c=0; c < SCREEN_NR; c++){
        for(int k=0; k < SCREEN_NC; k++){
            printf(".");
        }
        printf("\n");
    }
    cell *aux = vivosAct->head;
    while(aux){
        if(validaPos(aux->x, aux->y)){
            gotoxy(aux->x, aux->y);
            setColor(theme(0,ALIVE_CLR));
            printf("#");
            gotoxy(0,0);
        }
        aux=aux->sig;
    }
}

int checkaVecindad(cell *centro, cell *ini, char mapaLoc[][3]){ //checa las 9 posiciones adyacentes a la celula centro
    int vecinos = 0;
//  checa en el vector de celulas vivas si alguna es adyacente a centro, empieza a buscar en ini y checa las celulas que estan cerca a ini en el vector
    cell *atras = ini;
    while(atras){
        if(abs(cmp(atras, centro)) > 2) break; //como el vector esta ordenado, si ya te alejaste mucho, puedes dejar de buscar

        if(abs(atras->x - centro->x) <= 1 && abs(atras->y - centro->y) <= 1){
            mapaLoc[1+(atras->x - centro->x)][1+(atras->y - centro->y)]=1;
            vecinos++;
        }
        atras=atras->ant;
    }

    cell *adelante = ini->sig;
    while(adelante){
        if(abs(cmp(adelante, centro)) > 2) break;

        if(abs(adelante->x - centro->x) <= 1 && abs(adelante->y - centro->y) <= 1){
            mapaLoc[1+(adelante->x - centro->x)][1+(adelante->y - centro->y)]=1;
            vecinos++;
        }
        adelante=adelante->sig;
    }
    return vecinos;
}

int updateGen(vecCells act, cell *mueren[], vecCells *nacen){
    cell *i=act.head;
    int posMuertos = 0;

    char mapaLoc[3][3];
    while(i){ //checa todas las celulas vivas para ver si alguna muere
        for(int c=0; c < 3; c++){
            for(int k=0; k < 3; k++)
                mapaLoc[c][k]=0;
        }

        int vecinos = checkaVecindad(i, i, mapaLoc)-1;

        for(int c=0;c < 3; c++){ //checa si alguna las celulas muertas adyacentes a i debe nacer
            for(int k=0; k < 3; k++){
                if(mapaLoc[c][k]) continue;

                int x = c+i->x-1;
                int y = k+i->y-1;
                cell *aux = creaCell(x, y);

                char mapaAux[3][3];
                int cont = checkaVecindad(aux, i, mapaAux);

                if(cont == 3){
                    inserta(nacen, x, y); //inserta se encarga de no tener duplicados, asi que no importa que se cheque una misma posicion mas de una vez
                }
                free(aux);
            }
        }

        if(vecinos < 2 || vecinos > 3){
            mueren[posMuertos++]=i;
        }

        i=i->sig;
    }
    return posMuertos;
}

void updateMuertos(vecCells *vivosAct, cell *mueren[], int muertos){
    for(int c=0; c < muertos; c++){
        if(validaPos(mueren[c]->x, mueren[c]->y)){
            gotoxy(mueren[c]->x, mueren[c]->y);
            setColor(theme(0,DEAD_CLR));
            printf(".");
            gotoxy(0,0);
        }
        borra(vivosAct, mueren[c]);
    }
}

int updateNacen(vecCells *vivosAct, vecCells *nacen){
    int nacidos = 0;
    while(nacen->head){
        nacidos++;

        if(validaPos(nacen->head->x, nacen->head->y)){
            gotoxy(nacen->head->x, nacen->head->y);
            setColor(theme(0,ALIVE_CLR));
            printf("#");
            gotoxy(0,0);
        }
        inserta(vivosAct, nacen->head->x, nacen->head->y);
        borra(nacen, nacen->head);
    }
    return nacidos;
}

void printFooter(int gen, int numVivos){
    setColor(theme(0,TEXT_CLR));
    gotoxy(0,SCREEN_NR);
    printf("                                                                  "); //para borrar lo que sea que este ahi antes
    gotoxy(0,SCREEN_NR);
    printf("GEN: %d     Poblacion: %d\n", gen, numVivos);
    gotoxy(0,0);
}

int main(){
    int numVivos=0;
    clearScreen();
    gotoxy(0,0);

    config();   //toma la informacion para la configuracion
    getchar();

    vecCells *vivosAct = (vecCells *) malloc(sizeof(vecCells));
    if(!setup(mundo(0), vivosAct, &numVivos)) return 1; //agarra el mundo del archivo txt

    printMapaIni(vivosAct);

    int gen=0;
    while(vivosAct->head){
        printFooter(gen, numVivos);

        cell **mueren = (cell **) malloc(numVivos*sizeof(cell *));
        vecCells *nacen = (vecCells *) malloc(sizeof(vecCells));
        iVec(nacen);

        if(mode(0) == 1) getchar(); //mode() regresa 1 si la configuracion dice que se avanza manualmente
        else delay(speed(0)); //y 2 si es automatico, speed() regresa el delay que se tiene al avanzar
        gotoxy(0,0);

        int muertos = updateGen(*vivosAct, mueren, nacen); //procesa todas las celulas vivas y las que potencialmente puede nacer, regresa cuantas celulas murieron
        updateMuertos(vivosAct, mueren, muertos);   //borra las celulas que murieron, los quita del arreglo vivosAct
        int nacidos=updateNacen(vivosAct, nacen);   //pinta las celulas que nacieron, regresa cuantas nacieron y los agrega a vivosAct

        free(nacen);
        free(mueren);
        numVivos-=muertos;
        numVivos+=nacidos;
        gen++;
    }
    free(vivosAct);
    clearScreen();
    gotoxy(0,0);
    setColor(2);
    printf("\n\tExtincion");

    return 0;
}
