#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <ncurses.h> 
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sox.h>

#define Length 32
#define Height 10
#define NBboxcol (3+2*(col-1))
#define NBboxlin (3+2*(lin-1))

typedef struct
{
	int x; 
	int y;
}	snow;

snow flakeStart[200];
snow flakeStop[65];

int L; // L pour Ligne 
int C; // C pour Colonne

char Welcome[33][137];
char Congratulation[22][135];
char Credits[46][122];
int Kyu[7][25];
int Cat[17][22];
int Secret[17][18];
int Eiffel[17][24];
int Nimrod[3][24];
int Whale[14][22];
int Crane[16][19];
int Flower[8][7];
int Heart[16][21];
int Esiea[15][24];
int Paris[17][25];

void ncurses_initialiser();
void colors();
void ncurses_souris();
int click_souris();
char key_pressed();
void AFFICHAGE_PRESS_KEY(int MaxY, int MaxX);
void AFFICHAGE_CREDITS(char TAB[46][122], int MaxY, int MaxX);
void AFFICHAGE_WELCOME(char TAB[33][137], int MaxY, int MaxX);
void AFFICHAGE_CONGRATULATION(char TAB[22][135], int MaxY, int MaxX);
void REMPLISSAGE_CREDITS();
void REMPLISSAGE_WELCOME();
void REMPLISSAGE_CONGRATULATION();
void STARS(int MaxY, int MaxX);
void HOME_PAGE(int MaxY, int MaxX);
void RANDOM_MENU(int MaxY, int MaxX, int dev);
void RANDOM_SIZE_AFFICHAGE(int MaxY, int MaxX);
void RANDOM_SIZE_OK(int MaxY, int MaxX);
void RANDOM_SIZE_LINE(int *nl, int MaxY, int MaxX);
void RANDOM_SIZE_COL(int *nl, int *nc, int MaxY, int MaxX);
void RANDOM_SIZE_CALL(int *nl, int *nc, int MaxY, int MaxX);
void PICTURES_MENU(int MaxY, int MaxX);
void LETTERS_MENU(int MaxY, int MaxX);
void VALID_CHOICE(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int ExitReplay, int dev);
void CREDITS_MENU(int MaxY, int MaxX, int dev);
void EXIT_MENU(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int ExitReplay, int dev);
int UPDATE_SNOWFLAKES(int MaxY, int MaxX, int StartStop);
int SNOWFLAKES(int MaxY, int MaxX, int StartStop);
void RETURN_MENU_AFFICHAGE(int MaxY, int MaxX);
void PATTERN(int MaxY, int MaxX);
void DRAW_TAB(int lin, int col, int TAB[lin][col]);
void INIT_TAB(int lin, int col, int TAB[lin][col]);
void SHOW_TAB(int lin, int col, int TAB[lin][col]);
void SHOW_FLAGTAB(int lin, int col, int FLAGTAB[lin][col]);
void JUMP_LEFT(int LLEFT, int CLEFT);
void SHOW_LEFT(int LLEFT, int CLEFT, int compteur);
void JUMP_UP(int LUP, int CUP);
void SHOW_UP(int LUP, int CUP, int compteur);
void FILL_TAB(int lin, int col, int TAB[lin][col]);
void INITFLAG_TAB(int lin, int col, int TAB[lin][col]);
int MID_CLICK(int L, int C);
int FORM_CONDITION(int L, int Ctemp, int lin, int col, int FLAGTAB[lin][col]);
void DRAW_CLICK(int L, int C, int temp);
void LINE_TEST(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col]);
void COL_TEST(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col]);
int END_GAME(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col]);
void SHOW_PATTERN(int lin, int col, int TAB[lin][col]);
void REMPLISSAGE_PARIS();
void PARIS_MODE(int lin, int col, int Paris[17][25], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_PARIS(int MaxY, int MaxX, int dev);
void REMPLISSAGE_ESIEA();
void ESIEA_MODE(int lin, int col, int Esiea[15][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_ESIEA(int MaxY, int MaxX, int dev);
void REMPLISSAGE_HEART();
void HEART_MODE(int lin, int col, int Heart[16][21], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_HEART(int MaxY, int MaxX, int dev);
void REMPLISSAGE_CRANE();
void CRANE_MODE(int lin, int col, int Crane[16][19], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_CRANE(int MaxY, int MaxX, int dev);
void REMPLISSAGE_FLOWER();
void FLOWER_MODE(int lin, int col, int Flower[8][7], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_FLOWER(int MaxY, int MaxX, int dev);
void REMPLISSAGE_WHALE();
void WHALE_MODE(int lin, int col, int Whale[14][22], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_WHALE(int MaxY, int MaxX, int dev);
void REMPLISSAGE_NIMROD();
void NIMROD_MODE(int lin, int col, int Nimrod[3][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_NIMROD(int MaxY, int MaxX, int dev);
void REMPLISSAGE_EIFFEL();
void EIFFEL_MODE(int lin, int col, int Eiffel[17][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_EIFFEL(int MaxY, int MaxX, int dev);
void REMPLISSAGE_SECRET();
void SECRET_MODE(int lin, int col, int Secret[17][18], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_SECRET(int MaxY, int MaxX, int dev);
void REMPLISSAGE_CAT();
void CAT_MODE(int lin, int col, int Cat[17][22], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_CAT(int MaxY, int MaxX, int dev);
void REMPLISSAGE_KYU();
void KYU_MODE(int lin, int col, int Kyu[7][25], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void INIT_KYU(int MaxY, int MaxX, int dev);
void INIT_RANDOM_MODE(int MaxY, int MaxX, int dev);
void RANDOM_MODE(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev);
void RJUMP(int mvL, int mvC);
void RRIGHT(int mvL, int mvC);
void REFRESH_PATTERN(int lin, int col, int FLAGTAB[lin][col]);
void REFRESH_CLICK(int lin, int col, int FLAGTAB[lin][col]);
void VALID_CLICK(int MaxY, int MaxX);
void EXIT_GAME(int MaxY, int MaxX);
void LETTERS_PAGE(int MaxY, int MaxX, int dev);
void PICTURES_PAGE(int MaxY, int MaxX, int dev);
void RANDOM_PAGE(int MaxY, int MaxX, int dev);
void MENU_THEME();
void MAIN_MENU(int MaxY, int MaxX, int dev);
void LANCEMENT_JEU();
int main();

































