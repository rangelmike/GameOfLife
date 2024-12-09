#ifndef CONFIG_H
#define CONFIG_H

#define NUM_WORLDS 7
#define ALIVE_CLR 0
#define DEAD_CLR 1
#define TEXT_CLR 2
#define NUM_THEMES 7

int mode(int i);
char *mundo(int i);
int theme(int i, int cual);
int speed(int i);
void customTheme(int i);
void config();

#endif // CONFIG_H
