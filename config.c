#include "config.h"
#include "screen.h"
#include <string.h>
#include <math.h>
//en casi todas estas funciones, 0 significa no cambiar nada, cualquier otra cosa es cambiar la configuracion
int mode(int i){
    static int m = -1;
    if(i) m=!(i%2)+1; //asegurar que m sea 1 o 2
    return m; //1 manual, 2 auto
}

char *mundo(int i){
    static int selected = 1;
    static char *worlds[] = {"custom.txt", "gosperGun.txt", "pi(matusalem).txt", "lineInf.txt", "osciladores.txt", "r(matusalem).txt", "diamond.txt"};
    if(i) selected = i;
    if(selected > NUM_WORLDS) selected = 1;
    return worlds[selected-1];
}

int theme(int i, int cual){
    static int selected = 1;
    static int custom[3] = {-1,-1,-1};
    static int temas[][3] = {{I_WHT, I_WHT, I_WHT}, {I_GRN, I_GRN, I_GRN}, {I_MAG, I_YEL, I_WHT}, {I_YEL,I_MAG,I_WHT}, {I_WHT,I_GRN,I_CYN}, {I_RED, I_GRN, I_WHT}, {I_CYN, I_WHT, I_GRN} }; //{VIVO, MUERTO, TEXTO}
    if(i < 0){ //numeros negativos para indicar que se esta poniendo un tema customizado
        custom[cual] = i*-1;
        return 0;
    }
    if(i) selected = i; //numero positivo para seleccionar uno distinto de los predeterminados, si es 0 solo regresa la ultima seleccion que se hizo
    if(selected > NUM_THEMES) selected = 1;
    cual = cual%3;
    if(custom[0] > 0) return custom[cual]; //si el ususario escogio el tema customizado, regresa ese
    return temas[selected-1][cual]; //si no, regresa uno de los determinados
}

int speed(int i){
    static int s = 1;
    if(i) s=i;
    return 101-s;
}

void customTheme(int i){
    if(i > 2) return;
    char *simbolos[] = {"#", "..", "abc"};
    char *mensaje[] = {"celulas vivas", "celulas muertas", "texto"};
    int aux;
    do{
        clearScreen();
        gotoxy(0,0);
        printf("Color para %s:\n", mensaje[i]);
        for(int c=1; c <= N_COLORS; c++){
            setColor(2);
            printf("  %d.- ", c);
            setColor(c);
            printf("%s", simbolos[i]);
        }
        setColor(2);
        gotoxy(strlen("Color para : ") + strlen(mensaje[i]), 0);
        scanf("%d", &aux);
    }while(aux < 1 || aux > N_COLORS);
    theme(-aux, i);
    customTheme(i+1);
}

void config(){
    setColor(2);

    int aux=0; //seleccionar si es modo manual o automatico
    do{
        clearScreen();
        gotoxy(0,0);
        printf("Selecciona modo:\n\t1.-Manual\t2.-Automatico");
        gotoxy(strlen("Selecciona modo: "), 0);
        scanf("%d", &aux);
    }while(aux < 1 || aux > 2);
    if(aux == 2){
        int aux2;
        do{
            clearScreen();
            gotoxy(0,0);
            printf("Introduce la velocidad(1-100): ");
            scanf("%d", &aux2);
        }while(aux2 < 1 || aux2 > 100);
        speed(aux2);
    }
    mode(aux);

    do{ //selecciona la configuracion inicial de las celulas
        clearScreen();
        gotoxy(0,0);
        printf("Selecciona mundo inicial:\n");
        for(int c=1; c <= NUM_WORLDS; c++){
            printf("    %d.-%s", c,mundo(c));
        }
        gotoxy(strlen("Selecciona mundo inicial: "), 0);
        scanf("%d", &aux);
    }while(aux < 1 || aux > NUM_WORLDS);
    mundo(aux);

    do{ //selecciona el color de las cosas
        clearScreen();
        setColor(2);
        gotoxy(0,0);
        printf("Selecciona el tema:\n");
        for(int c=1; c <= NUM_THEMES; c++){
            setColor(2);
            printf("    %d.- (",c);
            setColor(theme(c, ALIVE_CLR));
            printf("# ");
            setColor(theme(c, DEAD_CLR));
            printf(". ");
            setColor(theme(c, TEXT_CLR));
            printf("abc");
            setColor(2);
            printf(")");
        }
        setColor(2);
        printf("    %d.- Custom", NUM_THEMES+1);
        gotoxy(strlen("Selecciona el tema: "), 0);
        scanf("%d", &aux);
    }while(aux < 1 || aux > NUM_THEMES+1);
    if(aux == NUM_THEMES+1) customTheme(0);
    else theme(aux,0);

    gotoxy(0,0);
}
