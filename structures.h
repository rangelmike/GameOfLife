#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Cell{
    int x,y;
    struct Cell *ant;
    struct Cell *sig;
}cell;

typedef struct{
    cell *head;
    cell *tail;
}vecCells;

void iVec(vecCells* vec);
cell *creaCell(int x, int y);
int cmp(cell *a, cell *b);
void inserta(vecCells *vec, int x, int y);
void borra(vecCells *vec, cell *c);

#endif // STRUCTURES_H
