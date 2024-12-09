#include "structures.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void iVec(vecCells* vec){
    vec->head=vec->tail=NULL;
}

cell* creaCell(int x, int y){
    cell *n = (cell *) malloc(sizeof(cell));
    if(!n) return n;
    n->x=x;
    n->y=y;
    n->ant=n->sig=NULL;
    return n;
}

int cmp(cell *a, cell *b){  //ordena segun su distancia al origen
    if(!a || !b) return 0;
    int da = abs(a->x)+abs(a->y);
    int db = abs(b->x)+abs(b->y);
    if(da-db) return da-db;
    if(a->x > b->x) return 1;
    if(a->x < b->x) return -1;
    if(a->y > b->y)return 1;
    if(a->y < b->y)return -1;
    return 0;
}

void inserta(vecCells *vec, int x, int y){ //inserta en el vector de celulas, manteniendolo ordenado
    cell *nuevo = creaCell(x,y);
    if(!nuevo) return;
    if(vec->head == NULL){
        vec->head=vec->tail=nuevo;
        return;
    }
    if(cmp(vec->head, nuevo) > 0){
        nuevo->sig=vec->head;
        vec->head->ant=nuevo;
        vec->head=nuevo;
        return;
    }

    cell *pos=vec->head;
    while(pos != vec->tail){
        if(cmp(pos->sig, nuevo) == 0){ //evita insertar celulas con las mismas coordenadas
            free(nuevo);
            return;
        }
        if(cmp(pos->sig, nuevo) > 0) break;
        pos=pos->sig;
    }
    if(!cmp(pos, nuevo)) return;
    if(pos == vec->tail)
        vec->tail=nuevo;
    nuevo->sig=pos->sig;
    pos->sig=nuevo;
    nuevo->ant=pos;
    if(nuevo->sig) nuevo->sig->ant=nuevo;
}

void borra(vecCells *vec, cell *c){
    if(!c) return;
    if(vec->head == c || vec->tail == c){
//        printf("%p\n", c);
        if(vec->head == c){
            vec->head=c->sig;
            if(c->sig) c->sig->ant=NULL;
        }
        if(vec->tail == c){
            vec->tail=c->ant;
            if(c->ant) c->ant->sig=NULL;
        }
        free(c);
        return;
    }
    c->ant->sig = c->sig;
    c->sig->ant = c->ant;
    free(c);
}
