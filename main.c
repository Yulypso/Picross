
											       /* PICROSS GAME Project S2 */


/*_______________________________________________________________________________________________________________________________*/
// Directive de préprocesseur
#include "main.h"


/*_______________________________________________________________________________________________________________________________*/

// Initialisation de ncurses
void ncurses_initialiser() 
{
  initscr();	        // Démarre le mode ncurses 
  cbreak();	        	// Pour les saisies clavier (desac. mise en buffer)
  noecho();             // Désactive l'affichage des caractères saisis 
  keypad(stdscr, TRUE);	// Active les touches spécifiques 
  refresh();            // Met a jour l'affichage */
  curs_set(FALSE);      // Masque le curseur */
}

/*_______________________________________________________________________________________________________________________________*/

// Initialisation des couleurs
void colors() 
{
  	if(has_colors() == FALSE) 
	{
    		endwin();
    		fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    		exit(EXIT_FAILURE);
  	}
  	
	start_color();
  	
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_BLUE, 300, 300, 1000);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_CYAN, 600, 800, 1000);
	init_color(COLOR_MAGENTA, 600, 400, 600); /*(== BROWN)*/

  assume_default_colors(COLOR_WHITE, COLOR_BLACK);
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
}

/*_______________________________________________________________________________________________________________________________*/

// Initialisation de la souris
void ncurses_souris() 
{
	if(!mousemask(ALL_MOUSE_EVENTS, NULL)) // Vérification de l'initialisation d'une souris
	{
		endwin();
    	fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    	exit(EXIT_FAILURE);
	}

	if(has_mouse() != TRUE) // Vérification de la détection d'une souris
	{
    	endwin();
    	fprintf(stderr, "Aucune souris n'est détectée.\n");
    	exit(EXIT_FAILURE);
	}
}


/*_______________________________________________________________________________________________________________________________*/

// Récuperation des coordonnées (y,x) du clic de la souris 
int click_souris()
{
	MEVENT event ;
	int ch;

	while((ch = getch()) != KEY_F(1)) 
	{
    	switch(ch) 
    	{
			case KEY_F(2): // Quitte la boucle
				return 1;

      		case KEY_MOUSE:
        		if(getmouse(&event) == OK)  
				{
	  				C = event.x;
	  				L = event.y;
	  				if(event.bstate & BUTTON1_CLICKED)
	  				{ 
	    				return 0;
	  				}
				}
    	}
 	 }
  return 0;
}


/*_______________________________________________________________________________________________________________________________*/

//Récupération des saisies de l'utilisateur sans bloquer le terminal
char key_pressed() 
{
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);

	if (c != EOF) 
	{
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}


/*_______________________________________________________________________________________________________________________________*/

void HOME_PAGE(int MaxY, int MaxX) 
{
	int i,j;

	STARS(MaxY, MaxX);
	
	for(i=0 ; i<=MaxY ; i++)					
	{
	//BOX PICROSS GAME
    mvprintw(MaxY/8+1,MaxX/2-5,"PICROSS GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			
			if(i==MaxY/8 && j==MaxX/2-11)
			{
				move(MaxY/8, MaxX/2-11);
				addch(ACS_ULCORNER);
			}	
	
			if(i==MaxY/8 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8 && j==MaxX/2+11)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+1 && j==MaxX/2-11)
			{
				move(MaxY/8+1,MaxX/2-11);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+1 && j==MaxX/2+11)
			{
				move(MaxY/8+1, MaxX/2+11);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+2 && j==MaxX/2-11)
			{
				move(MaxY/8+2, MaxX/2-11);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+2 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+2 && j==MaxX/2+11)
			{	
				move(MaxY/8+2, MaxX/2+11);
				addch(ACS_LRCORNER);
			}
		}

	attron(COLOR_PAIR(1));
	//BOX RANDOM MODE
	mvprintw(MaxY/8+6,MaxX/2-5,"RANDOM MODE");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+5 && j==MaxX/2-9)
			{
				move(MaxY/8+5,MaxX/2-9);
				addch(ACS_ULCORNER);	
			}
		
			if(i==MaxY/8+5 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+5 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+6 && j==MaxX/2-9)
			{
				move(MaxY/8+6,MaxX/2-9);
				addch(ACS_VLINE);
			}

			if(i==MaxY/8+6 && j==MaxX/2+9)
			{
				move(MaxY/8+6,MaxX/2+9);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+7 && j==MaxX/2-9)
			{
				move(MaxY/8+7,MaxX/2-9);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+7 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+7 && j==MaxX/2+9)	
			{
				addch(ACS_LRCORNER);
			}
		}
	attroff(COLOR_PAIR(1));
	
	attron(COLOR_PAIR(6));
	// BOX PICTURES MODE
	mvprintw(MaxY/8+10, MaxX/2-6, "PICTURES MODE");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2-9)
			{
				move(MaxY/8+9,MaxX/2-9);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+9 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-9)
			{
				move(MaxY/8+10,MaxX/2-9);
				addch(ACS_VLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2+9)
			{
				move(MaxY/8+10,MaxX/2+9);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2-9)
			{
				move(MaxY/8+11, MaxX/2-9);
				addch(ACS_LLCORNER);
			}
		
			if(i==MaxY/8+11 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2+9)
			{
				addch(ACS_LRCORNER);
			}
		}
	attroff(COLOR_PAIR(6));
		
	attron(COLOR_PAIR(3));
	// BOX LETTERS MODE
	mvprintw(MaxY/8+14, MaxX/2-6, "LETTERS MODE");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+13 && j==MaxX/2-9)
			{
				move(MaxY/8+13,MaxX/2-9);
				addch(ACS_ULCORNER);
			}
	
			if(i==MaxY/8+13 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+13 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+14 && j==MaxX/2-9)
			{
				move(MaxY/8+14,MaxX/2-9);
				addch(ACS_VLINE);
			}
			
			if(i==MaxY/8+14 && j==MaxX/2+9)
			{
				move(MaxY/8+14,MaxX/2+9);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+15 && j==MaxX/2-9)
			{
				move(MaxY/8+15,MaxX/2-9);
				addch(ACS_LLCORNER);
			}
		
			if(i==MaxY/8+15 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}
	
			if(i==MaxY/8+15 && j==MaxX/2+9)
			{
				addch(ACS_LRCORNER);
			}
		}
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(4));
	//BOX CREDITS
	mvprintw(MaxY/8+18, MaxX/2-3, "CREDITS");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+17 && j==MaxX/2-9)
			{
				move(MaxY/8+17,MaxX/2-9);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+17 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+17 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+18 && j==MaxX/2-9)
			{
				move(MaxY/8+18,MaxX/2-9);
				addch(ACS_VLINE);
			}
		
			if(i==MaxY/8+18 && j==MaxX/2+9)
			{
				move(MaxY/8+18,MaxX/2+9);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+19 && j==MaxX/2-9)
			{
				move(MaxY/8+19, MaxX/2-9);
				addch(ACS_LLCORNER);
			}
		
			if(i==MaxY/8+19 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+19 && j==MaxX/2+9)
			{
				addch(ACS_LRCORNER);
			}
		}
	attroff(COLOR_PAIR(4));

	attron(COLOR_PAIR(7));
	// BOX LEAVE THE GAME
	mvprintw(MaxY/8+22, MaxX/2-6, "LEAVE THE GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+21 && j==MaxX/2-9)
			{
				move(MaxY/8+21,MaxX/2-9);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+21 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+21 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+22 && j==MaxX/2-9)
			{
				move(MaxY/8+22,MaxX/2-9);
				addch(ACS_VLINE);
			}
		
			if(i==MaxY/8+22 && j==MaxX/2+9)
			{
				move(MaxY/8+22,MaxX/2+9);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+23 && j==MaxX/2-9)
			{
				move(MaxY/8+23, MaxX/2-9);
				addch(ACS_LLCORNER);
			}
		
			if(i==MaxY/8+23 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+23 && j==MaxX/2+9)
			{
				addch(ACS_LRCORNER);
			}
		}
	attroff(COLOR_PAIR(7));
	}
}


/*_______________________________________________________________________________________________________________________________*/

//MENU PRINCIPAL DU JEU
void MAIN_MENU(int MaxY, int MaxX, int dev)
{
	int flag=0; 

		HOME_PAGE(MaxY, MaxX);

//HOME_MENU
	while (flag == 0)
  	{
		click_souris();
		//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

		if (L <= MaxY/8+2 && L >= MaxY/8) 					//PICROSS GAME
		{
			if (C >= MaxX/2-11 && C <= MaxX/2+11) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				HOME_PAGE(MaxY, MaxX);
				MAIN_MENU(MaxY, MaxX, dev);	
  			}
		}
		    
		if (L <= MaxY/8+7 && L >= MaxY/8+5) 				//RANDOM
		{
			if(C >= MaxX/2-9 && C <= MaxX/2+9)  
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				RANDOM_PAGE(MaxY, MaxX, dev);
  			}
		}
	
	
		if (L >= MaxY/8+9 && L <= MaxY/8+11) 				//PICTURES
		{
			if (C >= MaxX/2-9 && C <= MaxX/2+9) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				PICTURES_PAGE(MaxY, MaxX, dev);
  			}
		}


		if (L >= MaxY/8+13 && L <= MaxY/8+15) 				//LETTERS
		{
			if (C >= MaxX/2-9 && C <= MaxX/2+9) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				LETTERS_PAGE(MaxY, MaxX, dev);	
  			}
		}

		if (L >= MaxY/8+17 && L <= MaxY/8+19) 				//CREDITS
		{
			if (C >= MaxX/2-9 && C <= MaxX/2+9) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				CREDITS_MENU(MaxY, MaxX, dev);			
  			}
		}

		if (L >= MaxY/8+21 && L <= MaxY/8+23) 				//LEAVE THE GAME
		{
			if (C >= MaxX/2-9 && C <= MaxX/2+9) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db &");
				flag=1;	
				EXIT_GAME(MaxY, MaxX);
				MAIN_MENU(MaxY, MaxX, dev);	
  			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void MENU_THEME()
{
	system("pkill play");
	system("play -q ./Music/Menu.mp3 repeat 99 vol -1db&");
}


/*_______________________________________________________________________________________________________________________________*/

void EXIT_GAME(int MaxY, int MaxX)  //quitter le jeu au menu 
{
	int i,j;
	clear();

	attron(A_UNDERLINE);
	mvprintw(MaxY/8+5, MaxX/2-20,"Do you really want to exit the game ?\n");			//dans le menu
	attroff(A_UNDERLINE);

	for(i=0 ; i<MaxY ; i++)
	{
		//BOX YES
		attron(COLOR_PAIR(1));
		mvprintw(MaxY/8+10,MaxX/2-11,"YES");
		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2-14)
			{
				move(MaxY/8+9,MaxX/2-14);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}
	
			if(i==MaxY/8+9 && j==MaxX/2-6)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-14)
			{
				move(MaxY/8+10,MaxX/2-14);
				addch(ACS_VLINE);
			}

			if(i==MaxY/8+10 && j==MaxX/2-6)
			{
				move(MaxY/8+10,MaxX/2-6);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2-14)
			{
				move(MaxY/8+11,MaxX/2-14);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2-6)
			{
				addch(ACS_LRCORNER);
			}
		}
		attroff(COLOR_PAIR(1));
	
		//BOX NO
		attron(COLOR_PAIR(3));
		mvprintw(MaxY/8+10,MaxX/2+9,"NO");
		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2+5)
			{
				move(MaxY/8+9,MaxX/2+5);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+9 && j==MaxX/2+13)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2+5)
			{
				move(MaxY/8+10,MaxX/2+5);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+10 && j==MaxX/2+13)
			{
				move(MaxY/8+10,MaxX/2+13);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2+5)
			{
				move(MaxY/8+11,MaxX/2+5);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2+13)
			{
				addch(ACS_LRCORNER);
			}
		}
		attroff(COLOR_PAIR(3));
	}
	VALID_CLICK(MaxY, MaxX);
}


/*_______________________________________________________________________________________________________________________________*/

void VALID_CLICK(int MaxY, int MaxX)
{
	int flag = 0;
	int temp = 0;

	while(flag==0) 								// quitter le jeu au menu (zone cliquée)
	{

	click_souris();
	
		if (L >= MaxY/8+9 && L <= MaxY/8+11) 
		{
			if(C >= MaxX/2-14 && C <= MaxX/2-6)  
			{
				flag=1;	
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				system("pkill play");
				system("play -q ./Music/Ending12.mp3 &");
				temp = SNOWFLAKES(MaxY, MaxX, 1);

				if(temp == 1)
				{
					endwin();
					system("pkill play");
					exit(-1);
				}
  			}
		}
		
		if (L <= MaxY/8+11 && L >= MaxY/8+9) 
		{
			if (C >= MaxX/2+5&& C <= MaxX/2+13) 
			{
				flag=1;
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				clear();
				HOME_PAGE(MaxY, MaxX);					
  			}
		}
	}
}

/*_______________________________________________________________________________________________________________________________*/

// Affichage graphique du tableau de jeu PICROSS
void DRAW_TAB(int lin, int col, int TAB[lin][col])
{
	int i,j;

	for(i=0; i< (Height + NBboxlin)+1; i++)
	{

		// Initialisation de la première ligne du tableau graphique "le couvercle" de la box a nombre n°1
		if(i == 0)
		{			
			for(j=0; j<NBboxcol; j++)
			{
				if(j == 0)
				{										
					move(i,Length);
					addch(ACS_ULCORNER);
				}

				if(j%2 == 1 && j>0 && j<(NBboxcol*3))
				{								
					addch(ACS_HLINE);
					addch(ACS_HLINE);
					addch(ACS_HLINE);							
				}

				if(j%2 == 0 && j>0 && j<NBboxcol-2)
				{					
					addch(ACS_TTEE);	
				}

				if(j == NBboxcol-1)
				{							
					addch(ACS_URCORNER);
				}
			}
			printw("\n");
		}

		// Initialisation des bordures et inter lignes entre le couvercle et le tableau de jeu
		if(i != 0 && i<Height)
		{			
			for(j=0; j<NBboxcol; j++)
			{
				if(j == 0)
				{										
					move(i,Length);
					addch(ACS_VLINE);
				}

				if(j%2 == 1 && j>0 && j<(NBboxcol*3))
				{							
					addch(' ');
					addch(' ');	
					addch(' ');	
				}

				if(j%2 == 0 && j>0 && j<NBboxcol-2)
				{		
					addch(ACS_VLINE);	
				}

				if(j == NBboxcol-1)
				{							
					addch(ACS_VLINE);
				}
			}
			printw("\n");
		}

		// Initialisation de la première ligne du tableau ainsi que le couverle de la box a nombre n°2
		if(i == Height)
		{
			for(j=0; j<Length+NBboxcol; j++)
			{
				if(j == 0)
				{										
					move(i,0);
					addch(ACS_ULCORNER);
				}

				if(j<Length && j>0 && j<Length+NBboxcol)
				{			
					addch(ACS_HLINE);	
				}

				if(j==Length && j>0)
				{								
					addch(ACS_PLUS);
				}

				if(j>Length && j%2 == 1 && j>0 && j<Length+(NBboxcol*3))
				{	
					addch(ACS_HLINE);
					addch(ACS_HLINE);
					addch(ACS_HLINE);	
				}

				if(j>Length && j%2 == 0 && j>0 && j<Length+NBboxcol-2)
				{			
					addch(ACS_PLUS);	
				}

				if(j == Length+NBboxcol-1)
				{								
					addch(ACS_RTEE);
				}
			}
			printw("\n");
		}

		// Initialisation des traits verticaux et des espaces vides
		if(i > Height && i%2 == 1 && i< Height + NBboxlin)
		{
			for(j=0; j<Length+NBboxcol; j++)
			{
				if(j == 0)
				{								
					move(i,0);
					addch(ACS_VLINE);
				}

				if(j<Length && j>0 && j<Length+NBboxcol)
				{	
					addch(' ');	
				}
	
				if(j==Length && j>0)
				{				
					addch(ACS_VLINE);
				}

				if(j>Length && j%2 == 1 && j>0 && j<Length+(NBboxcol*3))
				{
					addch(' ');
					addch(' ');
					addch(' ');
				}

				if(j>Length && j%2 == 0 && j>0 && j<Length+NBboxcol-2)
				{				
					addch(ACS_VLINE);	
				}
			
				if(j == Length+NBboxcol-1)
				{								
					addch(ACS_VLINE);
				}
			}
			printw("\n");
		}		

		// Initialisation des traits verticaux avec un 'T' et des lignes
		if(i > Height && i%2 == 0 && i< Height + NBboxlin-1)
		{
			for(j=0; j<Length+NBboxcol; j++)
			{
				if(j == 0)
				{							
					move(i,0);
					addch(ACS_LTEE);
				}

				if(j<Length && j>0 && j<Length+NBboxcol)	
				{						
					addch(ACS_HLINE);	
				}

				if(j==Length && j>0)
				{							
					addch(ACS_PLUS);
				}

				if(j>Length && j%2 == 1 && j>0 && j<Length+(NBboxcol*3))
				{	
					addch(ACS_HLINE);
					addch(ACS_HLINE);
					addch(ACS_HLINE);	
				}

				if(j>Length && j%2 == 0 && j>0 && j<Length+NBboxcol-2)
				{				
					addch(ACS_PLUS);	
				}

				if(j == Length+NBboxcol-1)
				{								
					addch(ACS_RTEE);
				}
			}
			printw("\n");
		}		

		//Initialisation de la base du tableau de jeu PICROSS 
		if(i == Height + NBboxlin)
		{
			for(j=0; j<Length+NBboxcol; j++)
			{
				if(j == 0)
				{										
					move(i-1,0);
					addch(ACS_LLCORNER);
				}

				if(j<Length && j>0 && j<Length+NBboxcol)
				{						
					addch(ACS_HLINE);	
				}

				if(j==Length && j>0)
				{							
					addch(ACS_BTEE);
				}

				if(j>Length && j%2 == 1 && j>0 && j<Length+(NBboxcol*3))
				{	
					addch(ACS_HLINE);
					addch(ACS_HLINE);	
					addch(ACS_HLINE);	
				}

				if(j>Length && j%2 == 0 && j>0 && j<Length+NBboxcol-2)
				{	
					addch(ACS_BTEE);	
				}

				if(j == Length+NBboxcol-1)
				{							
					addch(ACS_LRCORNER);
				}
			}
			printw("\n");
		}		
	}
}	


/*_______________________________________________________________________________________________________________________________*/ 

// Initialisation d'un tableau à 0 qui prendra des valeurs en fonction des clics de l'utilisateur 
void INITFLAG_TAB(int lin, int col, int TAB[lin][col])
{
	int i,j;

		for(i=0; i<lin; i++)
		{
			for(j=0; j<col; j++)
			{
				TAB[i][j] = 0;
			}
		}	
}


/*_______________________________________________________________________________________________________________________________*/

// Permet de se déplacer dans les lignes à gauche du tableau
void JUMP_LEFT(int LLEFT, int CLEFT)
{
	move(LLEFT, CLEFT);
}


/*_______________________________________________________________________________________________________________________________*/

// Permet d'afficher les nombres dans les lignes à gauche du tableau
void SHOW_LEFT(int LLEFT, int CLEFT, int compteur)
{
	move(LLEFT,CLEFT);
	printw("%d", compteur);
}


/*_______________________________________________________________________________________________________________________________*/

// Permet de se déplacer dans les colonnes au-dessus du tableau
void JUMP_UP(int LUP, int CUP)
{
	move(LUP, CUP);
}


/*_______________________________________________________________________________________________________________________________*/

// Permet d'afficher les nombres dans les colonnes au-dessus du tableau
void SHOW_UP(int LUP, int CUP, int compteur)
{
	move(LUP,CUP);
	printw("%d", compteur);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui utilise JUMP_UP, SHOW_UP, JUMP_LEFT, SHOW_LEFT pour afficher les nombres dans les lignes et colonnes à côté du tableau
void FILL_TAB(int lin, int col, int TAB[lin][col])  
{
	int i,j;
	int compteur1 = 0;		//pour les carrés
	int compteur2 = 0;		//pour les croix
	int compteur0 = 0;      //pour le cas où il n'y a rien sur lignes/colonnes
	int compteur0bis = 0;
	int LLEFT = 11;			//position de base du curseur pour écriture gauche
	int CLEFT = 2;
	int LUP = 1;			//position de base du curseur pour écriture haut
	int CUP = 34;

	for(i=0; i<lin; i++)
	{
		for(j=0; j<col; j++)
		{	
			if(TAB[i][j]==2)						//cas où = 2
			{
				compteur0++;
		
				if(compteur0 == col-1)
				{
					compteur0 = 0;
					SHOW_LEFT(LLEFT, CLEFT, compteur0);
				}
	
				if (compteur1 == 0 && j == col-1)  //cas où fin = 0 et compteur NON
				{
					//équivalent à un printw("\n");
					LLEFT+=2;
					CLEFT = 2;
					JUMP_LEFT(LLEFT, CLEFT);
					compteur1 = 0;
					compteur0 = 0;
				}	

				if (compteur1 >= 1 && j == col-1)  //cas où fin = 0 et compteur OUI
				{
					//équivalent à un printw("%d ",compteur1);
					SHOW_LEFT(LLEFT, CLEFT, compteur1);
					compteur1 = 0;
					compteur0 = 0;

					//équivalent à un printw("\n"); 
					LLEFT+=2;
					CLEFT = 2;
					JUMP_LEFT(LLEFT, CLEFT);
				}	

				if(compteur1 >= 1)				//cas où = 0 et compteur OUI
				{	
					//équivalent à un printw("%d ",compteur1);
					SHOW_LEFT(LLEFT, CLEFT, compteur1);

					CLEFT+=3;
					compteur1 = 0;
					compteur0 = 0;
				}
			}

			if(TAB[i][j]==1)					//cas où = 1 
			{
				compteur0 = 0;
				compteur1++;
				if(compteur1 >= 1 && j == col-1)	//cas où fin = 1 et compteur OUI
				{
					//équivalent à un printw("%d ",compteur1);
					SHOW_LEFT(LLEFT, CLEFT, compteur1);

					//équivalent à un printw("\n");
					LLEFT+=2;
					CLEFT = 2;
					JUMP_LEFT(LLEFT, CLEFT);
					compteur1 = 0;				
				}
			}
		}
	}
	printw("\n");


	for(j=0; j<col; j++)
	{
		for(i=0; i<lin; i++)
		{
			if(TAB[i][j]==2)							//cas où = 0
			{
				compteur0bis++;
		
				if(compteur0bis == lin-1)
				{
					compteur0bis = 0;
					SHOW_UP(LUP, CUP, compteur0bis);
				}

				if (compteur2 == 0 && i == lin-1)		//cas où fin = 0 et compteur NON
				{
					//équivalent à un printw("\n");
					LUP = 1;
					CUP+=4;
					JUMP_UP(LUP,CUP);
					compteur2 = 0;
					compteur0bis = 0;
				}	

				if (compteur2 >= 1 && i == lin-1)  		//cas où fin = 0 et compteur OUI
				{
					//équivalent à un printw("%d ",compteur2);
					SHOW_UP(LUP, CUP, compteur2);

					//équivalent à un printw("\n");
					LUP = 1;
					CUP+=4;
					JUMP_UP(LUP,CUP);
					compteur2 = 0;
					compteur0bis = 0;
				}	

				if(compteur2 >= 1)						//cas où = 0 et compteur OUI
				{	
					//équivalent à un printw("%d ",compteur2);
					SHOW_UP(LUP, CUP, compteur2);

					LUP++;
					compteur2 = 0;
					compteur0bis = 0;
				}
			}

			if(TAB[i][j]==1)							//cas où = 1 
			{
				compteur0bis = 0;
				compteur2++;
				if(compteur2 >= 1 && i == lin-1)		//cas où fin = 1 et compteur OUI
				{
					//équivalent à un printw("%d ",compteur2);
					SHOW_UP(LUP, CUP, compteur2);

					//équivalent à un printw("\n");
					LUP = 1;
					CUP+=4;
					JUMP_UP(LUP,CUP);
					compteur2 = 0;				
				}
			}
		}
	}
	printw("\n");
}


/*_______________________________________________________________________________________________________________________________*/

// Permet de centraliser le clic souris en une valeur qui est retournée
int MID_CLICK(int L, int C)
{
	int Ctemp = C;

	if(L%2==1 && C%2==1)
	{
		if(C<C+1 && (C+1)%4==2)
		{
			return Ctemp++;
		}
	
		if(C>C-1 && (C-1)%4==2)
		{
			return Ctemp--;
		}
	}

 	else if(L%2==1 && C%2==0)
	{
		return Ctemp;
	}
	return Ctemp;
}


/*_______________________________________________________________________________________________________________________________*/

// Renvoie une valeur entre 0 et 2 en fonction de la valeur de la case cliquée
// La case cliquée dépend de la valeur renvoyée par MID_CLICK
int FORM_CONDITION(int L, int Ctemp, int lin, int col, int FLAGTAB[lin][col])
{
	if((L%2 == 1 && C%2 == 0 && C%4 != 0) || (L%2 == 1 && C%2 == 1)) //CLick sur [ ][x][ ] ou Click sur [X][ ][X]
	{
	if((FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4])%3 == 0)
	{
		FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4] = 1;
		return 1;				
	}
			
	else if((FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4])%3 == 1)
	{
		FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4] = 2;
		return 2;
	}

	else if((FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4])%3 == 2)
	{
		FLAGTAB[((L-Height)/2)][(Ctemp-Length)/4] = 0;
    	return 0;
	}	
	}
	return 1;
}


/*_______________________________________________________________________________________________________________________________*/

// Affichage un symbole en fonction de la valeur renvoyée par FORM_CONDITION
void DRAW_CLICK(int L, int C, int temp)
{
	if(L%2 == 1 && C%2 == 0 && C%4 != 0)		
	{
		if(temp == 0)								//CLick sur [ ][x][ ]
		{
			mvaddch(L, C-1, ' ');	
			mvaddch(L, C, ' ');	
			mvaddch(L, C+1, ' ');	
			refresh();
		}

		else if(temp == 1)
		{
			system("play -q ./Music/V_click.mp3 vol -12db&");
			mvaddch(L, C-1, ACS_CKBOARD); //
			mvaddch(L, C+1, ACS_CKBOARD); //
			mvaddch(L, C, ACS_CKBOARD);
			refresh();
		}

		else if(temp == 2)
		{
			system("play -q ./Music/X_click.mp3 vol -12db");
			mvaddch(L, C-1, ' ');
			mvaddch(L, C, 'X');
			mvaddch(L, C+1, ' ');
			refresh();
		}
	}

	if(L%2 == 1 && C%2 == 1)						//Click sur [X][ ][X]
	{

		if(C < C+1 && (C+1)%4 == 2)					//Click sur [X][ ][ ]
		{
			if(temp == 0)
			{
				mvaddch(L, C+1, ' ');
				mvaddch(L, C, ' ');
				mvaddch(L, C+2, ' ');
				refresh();	
			}
			else if(temp == 1)
			{
				system("play -q ./Music/V_click.mp3 vol -12db&");
				mvaddch(L, C+1, ACS_CKBOARD);
				mvaddch(L, C, ACS_CKBOARD); //
				mvaddch(L, C+2, ACS_CKBOARD); //
				refresh();
			}
			else if(temp == 2)
			{
				system("play -q ./Music/X_click.mp3 vol -12db&");
				mvaddch(L, C+1, 'X');
				mvaddch(L, C, ' ');
				mvaddch(L, C+2, ' ');
				refresh();
			}
		}
	
		if(C > C-1 && (C-1)%4 == 2)					//Click sur [ ][ ][X]
		{
			if(temp == 0)
			{
				mvaddch(L, C-1, ' ');	
				mvaddch(L, C, ' ');
				mvaddch(L, C-2, ' ');
				refresh();
			}
			else if(temp == 1)
			{
				system("play -q ./Music/V_click.mp3 vol -12db&");
				mvaddch(L, C-1, ACS_CKBOARD);
				mvaddch(L, C, ACS_CKBOARD); //
				mvaddch(L, C-2, ACS_CKBOARD); //
				refresh();
			}
			else if(temp == 2)
			{
				system("play -q ./Music/X_click.mp3 vol -12db&");
				mvaddch(L, C, ' ');
				mvaddch(L, C-1, 'X');
				mvaddch(L, C-2, ' ');
				refresh();
			}
		}
	}
}

/*_______________________________________________________________________________________________________________________________*/

void RJUMP(int mvL, int mvC)
{
	move(mvL, mvC);
}


/*_______________________________________________________________________________________________________________________________*/

void RRIGHT(int mvL, int mvC)
{
	move(mvL, mvC);
}


/*_______________________________________________________________________________________________________________________________*/

void REFRESH_CLICK(int lin, int col, int FLAGTAB[lin][col])
{
	int i,j;
	int Lbase = Height+1;
	int Cbase = Length+2;
	int mvL=Lbase, mvC = Cbase;

	move(Lbase, Cbase);

	for(i=0; i<lin ; i++)
	{
		for(j=0; j<col ; j++)
		{
			if(FLAGTAB[i][j]==0)
			{
				mvaddch(mvL, mvC-1, ' ');
				mvaddch(mvL, mvC, ' ');
				mvaddch(mvL, mvC+1, ' ');
				mvC+=4;
				RRIGHT(mvL, mvC);
			}
			else if(FLAGTAB[i][j]==1)
			{
				mvaddch(mvL, mvC-1, ACS_CKBOARD);
				mvaddch(mvL, mvC, ACS_CKBOARD);
				mvaddch(mvL, mvC +1, ACS_CKBOARD);
				mvC+=4;
				RRIGHT(mvL, mvC);
			}
			else if(FLAGTAB[i][j]==2)
			{
				mvaddch(mvL, mvC-1, ' ');
				mvaddch(mvL, mvC, 'X');
				mvaddch(mvL, mvC+1, ' ');
				mvC+=4;
				RRIGHT(mvL, mvC);
			}
	
			if(i<lin && j==col-1)
			{
				mvL+=2;
				mvC = Cbase;
				RJUMP(mvL, mvC);
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

// Vérifie si la ligne à été correctement remplis par l'utilisateur si oui lui affiche le symbole V 
void LINE_TEST(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col])
{
	int i,j;
	int temp=0;

	for(i=0; i<lin ; i++)
	{
		for(j=0; j<col ; j++)
		{
			if(TAB[i][j]==FLAGTAB[i][j])
			{
				temp++;
			}
		
			if(temp == col)
			{		
				if(Height+1+i*2 < Height + lin*2)
				{
					move(Height+1+i*2, Length+col*4+2);
					attron(COLOR_PAIR(3));
					addch('V');
					attroff(COLOR_PAIR(3));
				}
			}

			else 
			{
				if(Height+1+i*2 < Height + lin*2)
				{
					move(Height+1+i*2, Length+col*4+2);
					addch(' ');
				}

			}
		}
		temp=0;
	}
	temp = 0;
}


/*_______________________________________________________________________________________________________________________________*/

// Vérifie si la colonne à été correctement remplis par l'utilisateur si oui lui affiche le symbole V 
void COL_TEST(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col])
{
	int i,j;
	int temp=0;

	for(j=0; j<col ; j++)
	{
		for(i=0; i<lin ; i++)
		{
			if(TAB[i][j]==FLAGTAB[i][j])
			{
				temp++;
			}
		
	
			if(temp == lin)
			{
				if(Length+2+j*4 < Length + col*4)
				{
					move(Height+lin*2+1 , Length+2+j*4);
					attron(COLOR_PAIR(3));
					addch('V');
					attroff(COLOR_PAIR(3));
				}
			}
		
			else 
			{	
				if(Length+2+j*4 < Length + col*4)
				{
					move(Height+lin*2+1 , Length+2+j*4);
					addch(' ');
				}
			}
		}
		temp = 0;
	}
	temp = 0;
}


/*_______________________________________________________________________________________________________________________________*/

// Test achaque clic de l'utilisateur si oui ou non tt le tableau a été completé correctment si oui fin du jeu 
int END_GAME(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col])
{
	int i,j;
	int win = 1;

	for(i=0; i<lin ; i++)
	{
		for(j=0; j<col ; j++)
		{
			if(FLAGTAB[i][j] != TAB[i][j])
			{
				win = 0;
			}
		}
	}
return win;
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_MENU(int MaxY, int MaxX, int dev) 
{
	int i,j;

	STARS(MaxY, MaxX);

	attron(COLOR_PAIR(1));
	for(i=0 ; i<=MaxY ; i++)					
	{
	//BOX PICROSS GAME
    mvprintw(MaxY/8+1,MaxX/2-5,"PICROSS GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			
			if(i==MaxY/8 && j==MaxX/2-11)
			{
				move(MaxY/8, MaxX/2-11);
				addch(ACS_ULCORNER);
			}	
	
			if(i==MaxY/8 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8 && j==MaxX/2+11)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+1 && j==MaxX/2-11)
			{
				move(MaxY/8+1,MaxX/2-11);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+1 && j==MaxX/2+11)
			{
				move(MaxY/8+1, MaxX/2+11);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+2 && j==MaxX/2-11)
			{
				move(MaxY/8+2, MaxX/2-11);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+2 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+2 && j==MaxX/2+11)
			{	
				move(MaxY/8+2, MaxX/2+11);
				addch(ACS_LRCORNER);
			}
		}

	//BOX PLAY GAME
	mvprintw(MaxY/8+10,MaxX/2-1,"PLAY");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2-9)
			{
				move(MaxY/8+9,MaxX/2-9);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+9 && j==MaxX/2+9)
			{
				addch(ACS_URCORNER);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-9)
			{
				move(MaxY/8+10,MaxX/2-9);
				addch(ACS_VLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2+9)
			{
				move(MaxY/8+10, MaxX/2+9);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2-9)
			{
				move(MaxY/8+11,MaxX/2-9);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2-9 && j<MaxX/2+9)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2+9)
			{
				addch(ACS_LRCORNER);
			}
		}
	}
	attroff(COLOR_PAIR(1));
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_PAGE(int MaxY, int MaxX, int dev)		
{
	int flag=0;
	RANDOM_MENU(MaxY, MaxX, dev);

	while (flag == 0)
  	{
		click_souris();
		
		if (L <= MaxY/8+11 && L >= MaxY/8+9)  					//PLAY
		{
			if(C >= MaxX/2-9 && C <= MaxX/2+9)  
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_RANDOM_MODE(MaxY, MaxX, dev);
  			}
		}
	
		if (L <= MaxY/8+2 && L >= MaxY/8) 						//HOME_PAGE
		{
			if (C >= MaxX/2-11 && C <= MaxX/2+11) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				HOME_PAGE(MaxY, MaxX);
				MAIN_MENU(MaxY, MaxX, dev);
  			}
		}
	}	
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui initialise le RANDOM_MODE
void INIT_RANDOM_MODE(int MaxY, int MaxX, int dev)
{
	int lin, col;

	RANDOM_SIZE_CALL(&lin, &col, MaxY, MaxX);
	clear();

	if(lin == 1902 && col == 2006)
	{
		system("pkill play");
		system("play -q ./Music/Hard_Desicion.mp3 repeat 99 vol -6db&");

		INIT_SECRET(MaxY, MaxX, dev);				//MODE SECRET
	}
	
	if(lin == 1111 && col == 1111)				//MODE DEVELOPPEUR
	{
		system("pkill play");
		system("play -q ./Music/devActivated.mp3 vol -12db&");
		clear();
		attron(COLOR_PAIR(3));
		mvprintw(MaxY/2-5, MaxX/2-10, "Developer Mode Activated...");
		attroff(COLOR_PAIR(3));
		mvprintw(MaxY-3,MaxX/2+33, "Press a Key to continue ...\n");
		getch();
		clear();
		dev = 1;
		MENU_THEME();
		HOME_PAGE(MaxY, MaxX);
		MAIN_MENU(MaxY, MaxX, dev);
	}

	if(lin == 2222 && col == 2222)
	{
		system("pkill play");
		system("play -q ./Music/devDesactivated.mp3 vol -12db&");
		clear();
		attron(COLOR_PAIR(3));
		mvprintw(MaxY/2-5, MaxX/2-10, "Developer Mode Desactivated...");
		attroff(COLOR_PAIR(3));
		mvprintw(MaxY-3,MaxX/2+33, "Press a Key to continue ...\n");
		getch();
		clear();
		dev = 0;
		MENU_THEME();
		HOME_PAGE(MaxY, MaxX);
		MAIN_MENU(MaxY, MaxX, dev);
	}
	
	int TAB[lin][col];
	int FLAGTAB[lin][col];

	INIT_TAB(lin, col, TAB);
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/StayWithMe.mp3 repeat 99 vol -10db&");

	RANDOM_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/


// Fonction qui appelle toutes les fonctions destinées au jeu RANDOM_MODE
void RANDOM_MODE(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	attron(COLOR_PAIR(1));
	DRAW_TAB(lin, col, TAB);
	attroff(COLOR_PAIR(1));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU
	//SHOW_TAB(lin, col, TAB);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, TAB); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	REFRESH_CLICK(lin, col, FLAGTAB);
	LINE_TEST(lin, col, TAB, FLAGTAB);
	COL_TEST(lin, col, TAB, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, TAB, FLAGTAB);
				COL_TEST(lin, col, TAB, FLAGTAB);
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, TAB, FLAGTAB, MaxY, MaxX, 2, dev); // RETURN MENU dans le jeu
  				}
			}
		}

		if(END_GAME(lin, col, TAB, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			EXIT_MENU(lin, col, TAB, FLAGTAB, MaxY, MaxX, 1, dev); //pour le cas "Replay"
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

// Initialisation d'un tableau de valeurs aléatoires entre 1 et 2
void INIT_TAB(int lin, int col, int TAB[lin][col])
{
	int i,j;
	srand(time(NULL));
		
		for(i=0; i<lin; i++)
		{
			for(j=0; j<col; j++)
			{
				TAB[i][j] = (rand()%2);

				if(TAB[i][j] == 0)
				{
					TAB[i][j] = 2;
				}
			}
		}	
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_SIZE_AFFICHAGE(int MaxY, int MaxX) 
{
	int i,j;
	
	STARS(MaxY, MaxX);
	
	attron(COLOR_PAIR(1));
	for(i=0 ; i<=MaxY ; i++)					
	{
	//BOX PICROSS GAME
    mvprintw(MaxY/8+1,MaxX/2-5,"PICROSS GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			
			if(i==MaxY/8 && j==MaxX/2-11)
			{
				move(MaxY/8, MaxX/2-11);
				addch(ACS_ULCORNER);
			}	
	
			if(i==MaxY/8 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8 && j==MaxX/2+11)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+1 && j==MaxX/2-11)
			{
				move(MaxY/8+1,MaxX/2-11);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+1 && j==MaxX/2+11)
			{
				move(MaxY/8+1, MaxX/2+11);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+2 && j==MaxX/2-11)
			{
				move(MaxY/8+2, MaxX/2-11);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+2 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+2 && j==MaxX/2+11)
			{	
				move(MaxY/8+2, MaxX/2+11);
				addch(ACS_LRCORNER);
			}
		}

	//BOX_LINES
	mvprintw(MaxY/8+6,MaxX/2-12,"Line");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+3 && j==MaxX/2-14)
			{
				move(MaxY/8+3,MaxX/2-14);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+3 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+3 && j==MaxX/2-6)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+4 && j==MaxX/2-14)
			{
				move(MaxY/8+4,MaxX/2-14);
				addch(ACS_VLINE);
			}

			if(i==MaxY/8+4 && j==MaxX/2-6)
			{
				move(MaxY/8+4,MaxX/2-6);
				addch(ACS_VLINE);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+5 && j==MaxX/2-14)
			{
				move(MaxY/8+5,MaxX/2-14);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+5 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}
	
			if(i==MaxY/8+5 && j==MaxX/2-6)
			{
				addch(ACS_LRCORNER);
			}
		}
	mvprintw(MaxY/8+4, MaxX/2, "x"); 

	//BOX COLUMN
	mvprintw(MaxY/8+6,MaxX/2+6,"Column");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+3 && j==MaxX/2+5)
			{
				move(MaxY/8+3,MaxX/2+5);
				addch(ACS_ULCORNER);
			}
	
			if(i==MaxY/8+3 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+3 && j==MaxX/2+13)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+4 && j==MaxX/2+5)
			{
				move(MaxY/8+4,MaxX/2+5);
				addch(ACS_VLINE);
			}

			if(i==MaxY/8+4 && j==MaxX/2+13)
			{
				move(MaxY/8+4,MaxX/2+13);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+5 && j==MaxX/2+5)
			{
				move(MaxY/8+5,MaxX/2+5);
				addch(ACS_LLCORNER);
			}
	
			if(i==MaxY/8+5 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+5 && j==MaxX/2+13)
			{
				addch(ACS_LRCORNER);
			}
		}
	}
	attroff(COLOR_PAIR(1));
	attron(A_UNDERLINE);
	mvprintw(MaxY/8+8,MaxX/2-16,"Enter here the size of the board ..."); 
	attroff(A_UNDERLINE);
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_SIZE_OK(int MaxY, int MaxX)
{
	int i,j;

	STARS(MaxY, MaxX);

	//BOX OK !
	mvprintw(MaxY/8+10,MaxX/2-1,"OK !");
	
	for(i=0 ; i<=MaxY ; i++)					
	{
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2-4)
			{
				move(MaxY/8+9,MaxX/2-4);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2-4 && j<MaxX/2+4)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+9 && j==MaxX/2+4)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-4)
			{
				move(MaxY/8+10,MaxX/2-4);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+10 && j==MaxX/2+4)
			{
				move(MaxY/8+10,MaxX/2+4);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2-4)
			{	
				move(MaxY/8+11, MaxX/2-4);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2-4 && j<MaxX/2+4)
			{	
				addch(ACS_HLINE);
			}
	
			if(i==MaxY/8+11 && j==MaxX/2+4)
			{
				addch(ACS_LRCORNER);
			}
		}
	}

	int flag=0;

	while(flag==0) 
	{
		click_souris();

		if (L >= MaxY/8+9 && L <= MaxY/8+11) 
		{
			if(C >= MaxX/2-4 && C <= MaxX/2+4)  
			{
				flag=1;
				clear();
 			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_SIZE_LINE(int *nl, int MaxY, int MaxX)
{
	RANDOM_SIZE_AFFICHAGE(MaxY, MaxX);
	echo();
	curs_set(TRUE); 

	while(mvscanw(MaxY/8+4, MaxX/2-10, "%d", nl)!=1 || *nl <= 0)
	{
		clear();
		noecho();
	    curs_set(FALSE);
		attron(A_UNDERLINE); 
		mvprintw(MaxY/8+7,MaxX/2-23,"ERROR : Please enter a line number greater than 0 ..." );
		attroff(A_UNDERLINE);
		RANDOM_SIZE_OK(MaxY, MaxX);

		RANDOM_SIZE_AFFICHAGE(MaxY, MaxX);
		echo();
		curs_set(TRUE);	
	}
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_SIZE_COL(int *nl, int *nc, int MaxY, int MaxX) 
{
	echo();
	curs_set(TRUE); 

	while(mvscanw(MaxY/8+4, MaxX/2+9, "%d", nc)!=1 || *nc <= 0)
	{
		clear();
		noecho();
	    curs_set(FALSE); 
		attron(A_UNDERLINE);
		mvprintw(MaxY/8+7,MaxX/2-23,"ERROR : Please enter a column number greater than 0 ..." );
		attroff(A_UNDERLINE);
		RANDOM_SIZE_OK(MaxY, MaxX);		

		RANDOM_SIZE_AFFICHAGE(MaxY, MaxX);
		echo();
		mvprintw(MaxY/8+4, MaxX/2-10, "%d", *nl);
		curs_set(TRUE);
	}
}


/*_______________________________________________________________________________________________________________________________*/

void RANDOM_SIZE_CALL(int *nl, int *nc, int MaxY, int MaxX)
{
	RANDOM_SIZE_AFFICHAGE(MaxY, MaxX);
	RANDOM_SIZE_LINE(nl, MaxY, MaxX);
	RANDOM_SIZE_COL(nl, nc, MaxY, MaxX);
	noecho();
	curs_set(FALSE); 
	refresh();
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_SECRET()
{
	int i,j;
	FILE * secret = NULL;
	secret = fopen("./Picture/Secret.txt", "r");
	
	for(i=0; i<18; i++)
	{
		for(j=0; j<18; j++)
		{
			Secret[i][j]= fgetc(secret);

			if(Secret[i][j] == '0')
			{
				Secret[i][j] = 2;
			}

			else if(Secret[i][j] == '1')
			{
				Secret[i][j] = 1;
			}
		}
		fgetc(secret);
	}

	fclose(secret);

	if(secret == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Secret.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(secret);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_SECRET(int MaxY, int MaxX, int dev)
{
	int lin = 17;
	int col = 18;
	int FLAGTAB[lin][col];

	REMPLISSAGE_SECRET();  	//INIT_TAB version SECRET
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	SECRET_MODE(lin, col, Secret, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu SECRET_MODE
void SECRET_MODE(int lin, int col, int Secret[17][18], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	attron(COLOR_PAIR(2));
	DRAW_TAB(lin, col, Secret);
	attroff(COLOR_PAIR(2));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	//SHOW_TAB(lin, col, Secret);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Secret); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Secret);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Secret, FLAGTAB);
	COL_TEST(lin, col, Secret, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Secret, FLAGTAB);
				COL_TEST(lin, col, Secret, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Secret, FLAGTAB, MaxY, MaxX, 8, dev); // RETURN MENU dans le jeu
  				}
			}
			
			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Secret, FLAGTAB, MaxY, MaxX, 5, dev); // SHOW PATERN dans le jeu (5 : pour mode secret)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Secret, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void PICTURES_MENU(int MaxY, int MaxX) 
{
	int i,j;

	STARS(MaxY, MaxX);

	attron(COLOR_PAIR(6));
	for(i=0 ; i<=MaxY ; i++)					
	{
	//BOX PICROSS GAME
    mvprintw(MaxY/8+1,MaxX/2-5,"PICROSS GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			
			if(i==MaxY/8 && j==MaxX/2-11)
			{
				move(MaxY/8, MaxX/2-11);
				addch(ACS_ULCORNER);
			}	
	
			if(i==MaxY/8 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8 && j==MaxX/2+11)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+1 && j==MaxX/2-11)
			{
				move(MaxY/8+1,MaxX/2-11);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+1 && j==MaxX/2+11)
			{
				move(MaxY/8+1, MaxX/2+11);
				addch(ACS_VLINE);
			}

		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+2 && j==MaxX/2-11)
			{
				move(MaxY/8+2, MaxX/2-11);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+2 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+2 && j==MaxX/2+11)
			{	
				move(MaxY/8+2, MaxX/2+11);
				addch(ACS_LRCORNER);
			}
		}

//BOX CAT
	mvprintw(MaxY/8+11,MaxX/2-22,"PICTURE 1");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-26)
			{
				move(MaxY/8+10, MaxX/2-26);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+10 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2-10)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+11 && j==MaxX/2-26)
			{
				move(MaxY/8+11,MaxX/2-26);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+11 && j==MaxX/2-10)
			{
				move(MaxY/8+11, MaxX/2-10);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+12 && j==MaxX/2-26)
			{
				move(MaxY/8+12, MaxX/2-26);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+12 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+12 && j==MaxX/2-10)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX WHALE
	mvprintw(MaxY/8+11,MaxX/2+14,"PICTURE 2");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2+10)
			{
				move(MaxY/8+10, MaxX/2+10);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+10 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2+26)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+11 && j==MaxX/2+10)
			{
				move(MaxY/8+11,MaxX/2+10);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+11 && j==MaxX/2+26)
			{
				move(MaxY/8+11, MaxX/2+26);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+12 && j==MaxX/2+10)
			{
				move(MaxY/8+12, MaxX/2+10);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+12 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+12 && j==MaxX/2+26)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX EIFFEL TOWER
	mvprintw(MaxY/8+17,MaxX/2-22,"PICTURE 3");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+16 && j==MaxX/2-26)
			{
				move(MaxY/8+16, MaxX/2-26);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+16 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+16 && j==MaxX/2-10)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+17 && j==MaxX/2-26)
			{
				move(MaxY/8+17,MaxX/2-26);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+17 && j==MaxX/2-10)
			{
				move(MaxY/8+17, MaxX/2-10);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+18 && j==MaxX/2-26)
			{
				move(MaxY/8+18, MaxX/2-26);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+18 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+18 && j==MaxX/2-10)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX CRANE
	mvprintw(MaxY/8+17,MaxX/2+14,"PICTURE 4");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+16 && j==MaxX/2+10)
			{
				move(MaxY/8+16, MaxX/2+10);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+16 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+16 && j==MaxX/2+26)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+17 && j==MaxX/2+10)
			{
				move(MaxY/8+17,MaxX/2+10);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+17 && j==MaxX/2+26)
			{
				move(MaxY/8+17, MaxX/2+26);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+18 && j==MaxX/2+10)
			{
				move(MaxY/8+18, MaxX/2+10);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+18 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+18 && j==MaxX/2+26)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX HEART
	mvprintw(MaxY/8+23,MaxX/2-22,"PICTURE 5");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+22 && j==MaxX/2-26)
			{
				move(MaxY/8+22, MaxX/2-26);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+22 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+22 && j==MaxX/2-10)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+23 && j==MaxX/2-26)
			{
				move(MaxY/8+23,MaxX/2-26);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+23 && j==MaxX/2-10)
			{
				move(MaxY/8+23, MaxX/2-10);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+24 && j==MaxX/2-26)
			{
				move(MaxY/8+24, MaxX/2-26);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+24 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+24 && j==MaxX/2-10)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX FLOWER
	mvprintw(MaxY/8+23, MaxX/2+14,"PICTURE 6");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+22 && j==MaxX/2+10)
			{
				move(MaxY/8+22, MaxX/2+10);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+22 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+22 && j==MaxX/2+26)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+23 && j==MaxX/2+10)
			{
				move(MaxY/8+23,MaxX/2+10);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+23 && j==MaxX/2+26)
			{
				move(MaxY/8+23, MaxX/2+26);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+24 && j==MaxX/2+10)
			{
				move(MaxY/8+24, MaxX/2+10);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+24 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+24 && j==MaxX/2+26)
			{	
				addch(ACS_LRCORNER);
			}
		}
	}
	attroff(COLOR_PAIR(6));
}


/*_______________________________________________________________________________________________________________________________*/

void PICTURES_PAGE(int MaxY, int MaxX, int dev)
{
	int flag = 0;
	PICTURES_MENU(MaxY, MaxX);

//PICTURES_MENU
	while (flag == 0)  									
  	{
		click_souris();

		if (L <= MaxY/8+2 && L >= MaxY/8) 						//HOME_PAGE
		{
			if (C >= MaxX/2-11 && C <= MaxX/2+11) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag =1;
				clear();
				HOME_PAGE(MaxY, MaxX);
				MAIN_MENU(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+10 && L <= MaxY/8+12) 					//CAT
		{
			if (C >= MaxX/2-26 && C <= MaxX/2+6) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_CAT(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+10 && L <= MaxY/8+12) 					//WHALE
		{
			if (C >= MaxX/2+10 && C <= MaxX/2+26) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_WHALE(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+16 && L <= MaxY/8+18) 					//EIFFEL TOWER
		{
			if (C >= MaxX/2-26 && C <= MaxX/2+6) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_EIFFEL(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+16 && L <= MaxY/8+18) 					//CRANE
		{
			if (C >= MaxX/2+10 && C <= MaxX/2+26) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_CRANE(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+22 && L <= MaxY/8+24) 					//HEART
		{
			if (C >= MaxX/2-26 && C <= MaxX/2+6) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_HEART(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+22 && L <= MaxY/8+24) 					//FLOWER
		{
			if (C >= MaxX/2+10 && C <= MaxX/2+26) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_FLOWER(MaxY, MaxX, dev);
  			}
		}
	}	
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_CAT()
{
	int i,j;
	FILE * cat = NULL;
	cat = fopen("./Picture/Cat.txt", "r");
	
	for(i=0; i<17; i++)
	{
		for(j=0; j<23; j++)
		{
			Cat[i][j]= fgetc(cat);

			if(Cat[i][j] == '0')
			{
				Cat[i][j] = 2;
			}

			else if(Cat[i][j] == '1')
			{
				Cat[i][j] = 1;
			}
		}
		fgetc(cat);
	}

	fclose(cat);

	if(cat == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Cat.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(cat);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_CAT(int MaxY, int MaxX, int dev)
{
	int lin = 17;
	int col = 22;
	int FLAGTAB[lin][col];

	REMPLISSAGE_CAT();  	//INIT_TAB version CAT
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	CAT_MODE(lin, col, Cat, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu CAT_MODE
void CAT_MODE(int lin, int col, int Cat[17][22], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Cat);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Cat);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Cat); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Cat);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Cat, FLAGTAB);
	COL_TEST(lin, col, Cat, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Cat, FLAGTAB);
				COL_TEST(lin, col, Cat, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Cat, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Cat, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Cat, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_WHALE()
{
	int i,j;
	FILE * whale = NULL;
	whale = fopen("./Picture/Whale.txt", "r");
	
	for(i=0; i<14; i++)
	{
		for(j=0; j<23; j++)
		{
			Whale[i][j]= fgetc(whale);

			if(Whale[i][j] == '0')
			{
				Whale[i][j] = 2;
			}

			else if(Whale[i][j] == '1')
			{
				Whale[i][j] = 1;
			}
		}
		fgetc(whale);
	}

	fclose(whale);

	if(whale == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Whale.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(whale);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_WHALE(int MaxY, int MaxX, int dev)
{
	int lin = 14;
	int col = 22;
	int FLAGTAB[lin][col];

	REMPLISSAGE_WHALE();  	//INIT_TAB version WHALE
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	WHALE_MODE(lin, col, Whale, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu WHALE_MODE
void WHALE_MODE(int lin, int col, int Whale[14][22], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Whale);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Whale);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Whale); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Whale);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Whale, FLAGTAB);
	COL_TEST(lin, col, Whale, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Whale, FLAGTAB);
				COL_TEST(lin, col, Whale, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Whale, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Whale, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Whale, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_EIFFEL()
{
	int i,j;
	FILE * eiffel = NULL;
	eiffel = fopen("./Picture/Eiffel.txt", "r");
	
	for(i=0; i<18; i++)
	{
		for(j=0; j<24; j++)
		{
			Eiffel[i][j]= fgetc(eiffel);

			if(Eiffel[i][j] == '0')
			{
				Eiffel[i][j] = 2;
			}

			else if(Eiffel[i][j] == '1')
			{
				Eiffel[i][j] = 1;
			}
		}
		fgetc(eiffel);
	}

	fclose(eiffel);

	if(eiffel == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Eiffel.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(eiffel);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_EIFFEL(int MaxY, int MaxX, int dev)
{
	int lin = 17;
	int col = 24;
	int FLAGTAB[lin][col];

	REMPLISSAGE_EIFFEL();  	//INIT_TAB version EIFFEL
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	EIFFEL_MODE(lin, col, Eiffel, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu EIFFEL_MODE
void EIFFEL_MODE(int lin, int col, int Eiffel[17][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Eiffel);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	//SHOW_TAB(lin, col, Eiffel);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Eiffel); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Eiffel);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Eiffel, FLAGTAB);
	COL_TEST(lin, col, Eiffel, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Eiffel, FLAGTAB);
				COL_TEST(lin, col, Eiffel, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Eiffel, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}
	
			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Eiffel, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Eiffel, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_CRANE()
{
	int i,j;
	FILE * crane = NULL;
	crane = fopen("./Picture/Crane.txt", "r");
	
	for(i=0; i<16; i++)
	{
		for(j=0; j<20; j++)
		{
			Crane[i][j]= fgetc(crane);

			if(Crane[i][j] == '0')
			{
				Crane[i][j] = 2;
			}

			else if(Crane[i][j] == '1')
			{
				Crane[i][j] = 1;
			}
		}
		fgetc(crane);
	}

	fclose(crane);

	if(crane == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Crane.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(crane);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_CRANE(int MaxY, int MaxX, int dev)
{
	int lin = 16;
	int col = 19;
	int FLAGTAB[lin][col];

	REMPLISSAGE_CRANE();  	//INIT_TAB version CRANE
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	CRANE_MODE(lin, col, Crane, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu CRANE_MODE
void CRANE_MODE(int lin, int col, int Crane[16][19], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Crane);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Crane);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Crane); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Crane);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Crane, FLAGTAB);
	COL_TEST(lin, col, Crane, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Crane, FLAGTAB);
				COL_TEST(lin, col, Crane, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Crane, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Crane, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Crane, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_HEART()
{
	int i,j;
	FILE * heart = NULL;
	heart = fopen("./Picture/Heart.txt", "r");
	
	for(i=0; i<16; i++)
	{
		for(j=0; j<22; j++)
		{
			Heart[i][j]= fgetc(heart);

			if(Heart[i][j] == '0')
			{
				Heart[i][j] = 2;
			}

			else if(Heart[i][j] == '1')
			{
				Heart[i][j] = 1;
			}
		}
		fgetc(heart);
	}

	fclose(heart);

	if(heart == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Heart.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(heart);
}

/*_______________________________________________________________________________________________________________________________*/

void INIT_HEART(int MaxY, int MaxX, int dev)
{
	int lin = 16;
	int col = 21;
	int FLAGTAB[lin][col];

	REMPLISSAGE_HEART();  	//INIT_TAB version HEART
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	HEART_MODE(lin, col, Heart, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu HEART_MODE
void HEART_MODE(int lin, int col, int Heart[16][21], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Heart);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Heart);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Heart); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Heart);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Heart, FLAGTAB);
	COL_TEST(lin, col, Heart, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Heart, FLAGTAB);
				COL_TEST(lin, col, Heart, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Heart, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Heart, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Heart, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_FLOWER()
{
	int i,j;
	FILE * flower = NULL;
	flower = fopen("./Picture/Flower.txt", "r");
	
	for(i=0; i<8; i++)
	{
		for(j=0; j<7; j++)
		{
			Flower[i][j]= fgetc(flower);

			if(Flower[i][j] == '0')
			{
				Flower[i][j] = 2;
			}

			else if(Flower[i][j] == '1')
			{
				Flower[i][j] = 1;
			}
		}
		fgetc(flower);
	}

	fclose(flower);

	if(flower == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Flower.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(flower);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_FLOWER(int MaxY, int MaxX, int dev)
{
	int lin = 8;
	int col = 7;
	int FLAGTAB[lin][col];

	REMPLISSAGE_FLOWER();  	//INIT_TAB version FLOWER
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	FLOWER_MODE(lin, col, Flower, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu FLOWER_MODE
void FLOWER_MODE(int lin, int col, int Flower[8][7], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(6));
	DRAW_TAB(lin, col, Flower);
	attroff(COLOR_PAIR(6));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Flower);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Flower); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Flower);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Flower, FLAGTAB);
	COL_TEST(lin, col, Flower, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Flower, FLAGTAB);
				COL_TEST(lin, col, Flower, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Flower, FLAGTAB, MaxY, MaxX, 6, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Flower, FLAGTAB, MaxY, MaxX, 3, dev); // SHOW PATERN dans le jeu (3 : pour mode image)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Flower, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void LETTERS_MENU(int MaxY, int MaxX) 
{
	int i,j;

	STARS(MaxY, MaxX);

	attron(COLOR_PAIR(3));
	for(i=0 ; i<=MaxY ; i++)					
	{
	//BOX PICROSS GAME
    mvprintw(MaxY/8+1,MaxX/2-5,"PICROSS GAME");
		for(j=0 ; j<=MaxX ; j++)
		{
			
			if(i==MaxY/8 && j==MaxX/2-11)
			{
				move(MaxY/8, MaxX/2-11);
				addch(ACS_ULCORNER);
			}	
	
			if(i==MaxY/8 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8 && j==MaxX/2+11)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+1 && j==MaxX/2-11)
			{
				move(MaxY/8+1,MaxX/2-11);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+1 && j==MaxX/2+11)
			{
				move(MaxY/8+1, MaxX/2+11);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+2 && j==MaxX/2-11)
			{
				move(MaxY/8+2, MaxX/2-11);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+2 && j>MaxX/2-11 && j<MaxX/2+11)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+2 && j==MaxX/2+11)
			{	
				addch(ACS_LRCORNER);
			}
		}
		
		//BOX KYU
	mvprintw(MaxY/8+11,MaxX/2-21,"LETTER 1");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-26)
			{
				move(MaxY/8+10, MaxX/2-26);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+10 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2-10)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+11 && j==MaxX/2-26)
			{
				move(MaxY/8+11,MaxX/2-26);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+11 && j==MaxX/2-10)
			{
				move(MaxY/8+11, MaxX/2-10);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+12 && j==MaxX/2-26)
			{
				move(MaxY/8+12, MaxX/2-26);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+12 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+12 && j==MaxX/2-10)
			{	
				addch(ACS_LRCORNER);
			}
		}

		//BOX NIMROD
	mvprintw(MaxY/8+11,MaxX/2+15,"LETTER 2");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2+10)
			{
				move(MaxY/8+10, MaxX/2+10);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+10 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+10 && j==MaxX/2+26)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+11 && j==MaxX/2+10)
			{
				move(MaxY/8+11,MaxX/2+10);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+11 && j==MaxX/2+26)
			{
				move(MaxY/8+11, MaxX/2+26);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+12 && j==MaxX/2+10)
			{
				move(MaxY/8+12, MaxX/2+10);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+12 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+12 && j==MaxX/2+26)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX ESIEA
	mvprintw(MaxY/8+17,MaxX/2-21,"LETTER 3");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+16 && j==MaxX/2-26)
			{
				move(MaxY/8+16, MaxX/2-26);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+16 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+16 && j==MaxX/2-10)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+17 && j==MaxX/2-26)
			{
				move(MaxY/8+17,MaxX/2-26);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+17 && j==MaxX/2-10)
			{
				move(MaxY/8+17, MaxX/2-10);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+18 && j==MaxX/2-26)
			{
				move(MaxY/8+18, MaxX/2-26);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+18 && j>MaxX/2-26 && j<MaxX/2-10)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+18 && j==MaxX/2-10)
			{	
				addch(ACS_LRCORNER);
			}
		}

//BOX PARIS
	mvprintw(MaxY/8+17,MaxX/2+15,"LETTER 4");
		for(j=0; j<MaxX; j++)
		{
			if(i==MaxY/8+16 && j==MaxX/2+10)
			{
				move(MaxY/8+16, MaxX/2+10);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+16 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+16 && j==MaxX/2+26)
			{	
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<=MaxX ; j++)				
		{	
			if(i==MaxY/8+17 && j==MaxX/2+10)
			{
				move(MaxY/8+17,MaxX/2+10);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+17 && j==MaxX/2+26)
			{
				move(MaxY/8+17, MaxX/2+26);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==MaxY/8+18 && j==MaxX/2+10)
			{
				move(MaxY/8+18, MaxX/2+10);
				addch(ACS_LLCORNER);
			}
			
			if(i==MaxY/8+18 && j>MaxX/2+10 && j<MaxX/2+26)
			{
				addch(ACS_HLINE);
			}
		
			if(i==MaxY/8+18 && j==MaxX/2+26)
			{	
				addch(ACS_LRCORNER);
			}
		}
	}
	attroff(COLOR_PAIR(3));
}


/*_______________________________________________________________________________________________________________________________*/

void LETTERS_PAGE(int MaxY, int MaxX, int dev)
{
	int flag = 0;
	LETTERS_MENU(MaxY, MaxX);

//LETTERS_MENU
	while (flag == 0)  									
  	{
		click_souris();

		if (L <= MaxY/8+2 && L >= MaxY/8) 						//HOME_PAGE
		{
			if (C >= MaxX/2-11 && C <= MaxX/2+11) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				HOME_PAGE(MaxY, MaxX);
				MAIN_MENU(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+10 && L <= MaxY/8+12) 					//KYU
		{
			if (C >= MaxX/2-26 && C <= MaxX/2+6) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_KYU(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+10 && L <= MaxY/8+12) 					//NIMROD
		{
			if (C >= MaxX/2+10 && C <= MaxX/2+26) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_NIMROD(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+16 && L <= MaxY/8+18) 					//ESIEA
		{
			if (C >= MaxX/2-26 && C <= MaxX/2+6) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_ESIEA(MaxY, MaxX, dev);
  			}
		}

		if (L >= MaxY/8+16 && L <= MaxY/8+18) 					//PARIS
		{
			if (C >= MaxX/2+10 && C <= MaxX/2+26) 
			{
				system("play -q ./Music/Menu_click.mp3 vol -12db&");
				flag=1;
				clear();
				INIT_PARIS(MaxY, MaxX, dev);
  			}
		}
	}	
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_KYU()
{
	int i,j;
	FILE * kyu = NULL;
	kyu = fopen("./Picture/Kyu.txt", "r");
	
	for(i=0; i<7; i++)
	{
		for(j=0; j<26; j++)
		{
			Kyu[i][j]= fgetc(kyu);

			if(Kyu[i][j] == '0')
			{
				Kyu[i][j] = 2;
			}

			else if(Kyu[i][j] == '1')
			{
				Kyu[i][j] = 1;
			}
		}
		fgetc(kyu);
	}

	fclose(kyu);

	if(kyu == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Kyu.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(kyu);
}

/*_______________________________________________________________________________________________________________________________*/

void INIT_KYU(int MaxY, int MaxX, int dev)
{
	int lin = 7;
	int col = 25;
	int FLAGTAB[lin][col];

	REMPLISSAGE_KYU();  	//INIT_TAB version KYU
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/IBelieve.mp3 repeat 99 vol -12db&");

	KYU_MODE(lin, col, Kyu, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu KYU_MODE
void KYU_MODE(int lin, int col, int Kyu[7][25], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(3));
	DRAW_TAB(lin, col, Kyu);
	attroff(COLOR_PAIR(3));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Kyu);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Kyu); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Kyu);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Kyu, FLAGTAB);
	COL_TEST(lin, col, Kyu, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB); 
				LINE_TEST(lin, col, Kyu, FLAGTAB);
				COL_TEST(lin, col, Kyu, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Kyu, FLAGTAB, MaxY, MaxX, 7, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Kyu, FLAGTAB, MaxY, MaxX, 4, dev); // SHOW PATERN dans le jeu  (4 : pour mode lettre)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Kyu, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_NIMROD()
{
	int i,j;
	FILE * nimrod = NULL;
	nimrod = fopen("./Picture/Nimrod.txt", "r");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<25; j++)
		{
			Nimrod[i][j]= fgetc(nimrod);

			if(Nimrod[i][j] == '0')
			{
				Nimrod[i][j] = 2;
			}

			else if(Nimrod[i][j] == '1')
			{
				Nimrod[i][j] = 1;
			}
		}
		fgetc(nimrod);
	}

	fclose(nimrod);

	if(nimrod == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Nimrod.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(nimrod);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_NIMROD(int MaxY, int MaxX, int dev)
{
	int lin = 3;
	int col = 24;
	int FLAGTAB[lin][col];

	REMPLISSAGE_NIMROD();  	//INIT_TAB version NIMROD
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/IBelieve.mp3 repeat 99 vol -12db&");
	NIMROD_MODE(lin, col, Nimrod, FLAGTAB, MaxY, MaxX, dev);
}

/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu NIMROD_MODE
void NIMROD_MODE(int lin, int col, int Nimrod[3][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	attron(COLOR_PAIR(3));
	DRAW_TAB(lin, col, Nimrod);
	attroff(COLOR_PAIR(3));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}
	//SHOW_TAB(lin, col, Nimrod);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Nimrod); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Nimrod);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Nimrod, FLAGTAB);
	COL_TEST(lin, col, Nimrod, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Nimrod, FLAGTAB);
				COL_TEST(lin, col, Nimrod, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Nimrod, FLAGTAB, MaxY, MaxX, 7, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
					if (L >= 4 && L <= 6) 
					{
						if(C >= 4 && C <= 22)  
						{
							system("play -q ./Music/Menu_click.mp3 vol -12db&");
							system("pkill -n");
							clear();
							EXIT_MENU(lin, col, Nimrod, FLAGTAB, MaxY, MaxX, 4, dev); // SHOW PATERN dans le jeu (4 : pour mode lettre)
  						}
					}
			}
		}

		if(END_GAME(lin, col, Nimrod, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_ESIEA()
{
	int i,j;
	FILE * esiea = NULL;
	esiea = fopen("./Picture/Esiea.txt", "r");
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<25; j++)
		{
			Esiea[i][j]= fgetc(esiea);

			if(Esiea[i][j] == '0')
			{
				Esiea[i][j] = 2;
			}

			else if(Esiea[i][j] == '1')
			{
				Esiea[i][j] = 1;
			}
		}
		fgetc(esiea);
	}

	fclose(esiea);

	if(esiea == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Esiea.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(esiea);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_ESIEA(int MaxY, int MaxX, int dev)
{
	int lin = 15;
	int col = 24;
	int FLAGTAB[lin][col];

	REMPLISSAGE_ESIEA();  	//INIT_TAB version ESIEA
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	ESIEA_MODE(lin, col, Esiea, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu ESIEA_MODE
void ESIEA_MODE(int lin, int col, int Esiea[15][24], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(3));
	DRAW_TAB(lin, col, Esiea);
	attroff(COLOR_PAIR(3));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Esiea);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Esiea); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Esiea);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Esiea, FLAGTAB);
	COL_TEST(lin, col, Esiea, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Esiea, FLAGTAB);
				COL_TEST(lin, col, Esiea, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Esiea, FLAGTAB, MaxY, MaxX, 7, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Esiea, FLAGTAB, MaxY, MaxX, 4, dev); // SHOW PATERN dans le jeu (3 : pour mode lettre)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Esiea, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_PARIS()
{
	int i,j;
	FILE * paris = NULL;
	paris = fopen("./Picture/Paris.txt", "r");
	
	for(i=0; i<17; i++)
	{
		for(j=0; j<25; j++)
		{
			Paris[i][j]= fgetc(paris);

			if(Paris[i][j] == '0')
			{
				Paris[i][j] = 2;
			}

			else if(Paris[i][j] == '1')
			{
				Paris[i][j] = 1;
			}
		}
		fgetc(paris);
	}

	fclose(paris);

	if(paris == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Paris.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(paris);
}


/*_______________________________________________________________________________________________________________________________*/

void INIT_PARIS(int MaxY, int MaxX, int dev)
{
	int lin = 17;
	int col = 25;
	int FLAGTAB[lin][col];

	REMPLISSAGE_PARIS();  	//INIT_TAB version PARIS
	INITFLAG_TAB(lin, col, FLAGTAB);
	refresh();

	system("pkill play");
	system("play -q ./Music/Beautiful.mp3 repeat 99 vol -12db&");
	PARIS_MODE(lin, col, Paris, FLAGTAB, MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction qui appelle toutes les fonctions destinées au jeu PARIS_MODE
void PARIS_MODE(int lin, int col, int Paris[17][25], int FLAGTAB[lin][col], int MaxY, int MaxX, int dev)
{
	int temp = 0;
	int Ctemp = 0;
	int win = 0;
	
	if(dev == 1)
	{
		PATTERN(MaxY, MaxX);						// AFFICHAGE POUR LE PATTERN
	}

	attron(COLOR_PAIR(3));
	DRAW_TAB(lin, col, Paris);
	attroff(COLOR_PAIR(3));

	RETURN_MENU_AFFICHAGE(MaxY, MaxX);			//AFFICHAGE POUR LE EXIT_MENU

	//SHOW_TAB(lin, col, Paris);
	//SHOW_FLAGTAB(lin, col, FLAGTAB);

	attron(COLOR_PAIR(2));
	FILL_TAB(lin, col, Paris); 				//Permet de compter les 1
	attroff(COLOR_PAIR(2));

	//SHOW_PATTERN(lin, col, Paris);
	REFRESH_CLICK(lin, col, FLAGTAB); 
	LINE_TEST(lin, col, Paris, FLAGTAB);
	COL_TEST(lin, col, Paris, FLAGTAB);

	while (click_souris() == 0 && win == 0) 
	{
		if(BUTTON1_CLICKED)
		{	
			//mvprintw(20, 0, "Vous avez cliqué sur la position (%d, %d)\n", (L), (C));

			if(L < Height+lin*2 &&  C < Length+col*4 && L > Height && C > Length)		//condition d'appartenance
			{	
				//SHOW_TAB(lin, col, TAB);
				//refresh();

				Ctemp = MID_CLICK(L, C);									
				temp = FORM_CONDITION(L, Ctemp, lin, col, FLAGTAB);
				attron(COLOR_PAIR(2));
				DRAW_CLICK(L, C, temp);
				attroff(COLOR_PAIR(2));
				//SHOW_FLAGTAB(lin, col, FLAGTAB);
				LINE_TEST(lin, col, Paris, FLAGTAB);
				COL_TEST(lin, col, Paris, FLAGTAB);
				refresh();
			}

			if (L >= 0 && L <= 2) 
			{
				if(C >= 4 && C <= 22)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					clear();
					EXIT_MENU(lin, col, Paris, FLAGTAB, MaxY, MaxX, 7, dev); // RETURN MENU dans le jeu
  				}
			}

			if(dev == 1)
			{
				if (L >= 4 && L <= 6) 
				{
					if(C >= 4 && C <= 22)  
					{
						system("play -q ./Music/Menu_click.mp3 vol -12db&");
						system("pkill -n");
						clear();
						EXIT_MENU(lin, col, Paris, FLAGTAB, MaxY, MaxX, 4, dev); // SHOW PATERN dans le jeu (4 : pour mode lettre)
  					}
				}
			}
		}

		if(END_GAME(lin, col, Paris, FLAGTAB) == 1)
		{
			win = 1;
			AFFICHAGE_CONGRATULATION(Congratulation, MaxY, MaxX);
			getch();
			clear();
			MENU_THEME();
			MAIN_MENU(MaxY, MaxX, dev);
			HOME_PAGE(MaxY, MaxX);
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void CREDITS_MENU(int MaxY, int MaxX, int dev)
{
	system("pkill play");
	system("play -q ./Music/Game_Over.mp3 repeat 99 vol -25db&");
	REMPLISSAGE_CREDITS();
	AFFICHAGE_CREDITS(Credits, MaxY, MaxX);
	getch();
	MENU_THEME();
	clear();
	MAIN_MENU(MaxY, MaxX, dev);
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_CREDITS()
{
	int i,j;
	FILE * credits = NULL;
	credits = fopen("./Picture/Credits.txt", "r");
	
	for(i=0; i<45; i++)
	{
		for(j=0; j<122; j++)
		{
			Credits[i][j]= fgetc(credits);
		}
		fgetc(credits);
	}

	fclose(credits);

	if(credits == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Credits.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(credits);
}


/*_______________________________________________________________________________________________________________________________*/

void AFFICHAGE_CREDITS(char TAB[46][122], int MaxY, int MaxX)
{
	attron(COLOR_PAIR(4));
	int i,j;
	system("clear");
	move(0,0);

	for(i=0; i<46; i++)
    {
        for(j=0; j<122; j++)
        {	
			printw("%c", TAB[i][j]);
        }
    }
	attroff(COLOR_PAIR(4));

	mvprintw(MaxY-3,MaxX/2+33, "Press a Key to continue ...\n");
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_WELCOME()
{
	int i,j;
	FILE * welcome = NULL;
	welcome = fopen("./Picture/Welcome.txt", "r");
	
	for(i=0; i<32; i++)
	{
		for(j=0; j<136; j++)
		{
			Welcome[i][j]= fgetc(welcome);
		}
		fgetc(welcome);
	}

	fclose(welcome);

	if(welcome == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Welcome.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(welcome);
}


/*_______________________________________________________________________________________________________________________________*/

void AFFICHAGE_WELCOME(char TAB[33][137], int MaxY, int MaxX)
{
	int i,j;
	system("clear");

	for(i=0; i<32; i++)
    {
        for(j=0; j<137; j++)
        {	
			printw("%c", TAB[i][j]);
        }
    }
}


/*_______________________________________________________________________________________________________________________________*/

void REMPLISSAGE_CONGRATULATION()
{
	int i,j;
	FILE * congratulation = NULL;
	congratulation = fopen("./Picture/Congratulation.txt", "r");
	
	for(i=0; i<22; i++)
	{
		for(j=0; j<135; j++)
		{
			Congratulation[i][j]= fgetc(congratulation);
		}
		fgetc(congratulation);
	}

	fclose(congratulation);

	if(congratulation == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s ", "./Picture/Congratulation.txt");
		endwin();
		exit(EXIT_FAILURE);
	}
	rewind(congratulation);
}


/*_______________________________________________________________________________________________________________________________*/

void AFFICHAGE_CONGRATULATION(char TAB[22][135], int MaxY, int MaxX)
{
	system("play -q ./Music/Win.mp3 vol -6db&");
	system("pkill -n");

	attron(COLOR_PAIR(5));
	int i,j;
	system("clear");
	move(4,0);

	for(i=0; i<22; i++)
    {
        for(j=0; j<135; j++)
        {
            printw("%c", TAB[i][j]);
        }
    }
	attroff(COLOR_PAIR(5));

	mvprintw(MaxY-2,MaxX/2+10, "Press a Key to continue ...\n");
}


/*_______________________________________________________________________________________________________________________________*/

void STARS(int MaxY, int MaxX)
{
	int TAB[MaxY][MaxX];

	for(int i=0; i<MaxY; i++)
	{
		for(int j=0; j<MaxX; j++)
		{
			TAB[i][j]=rand();
		}
	}

	for(int i=0; i<MaxY; i++)
	{
		for(int j=0; j<MaxX; j++)
		{
			if(TAB[i][j]%450 == 0)
			{
				mvaddch(i, j, '*');
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

int UPDATE_SNOWFLAKES(int MaxY, int MaxX, int StartStop)
{
	int i = 0;
	curs_set(FALSE);
    clear();

	if(StartStop == 0)
	{
		while(i < 200)
		{
    	    flakeStart[i].y += 1;
    	    if (flakeStart[i].y > MaxY + 200) 
			{
				return 1;
     	   }
     	   mvprintw(flakeStart[i].y, flakeStart[i].x, "*");
		i++;
		}
	}

	else if(StartStop == 1)
	{
		while(i < 65)
		{
    	    flakeStop[i].y += 1;
    	    if (flakeStop[i].y > MaxY + 65) 
			{
				return 1;
     	   }
     	   mvprintw(flakeStop[i].y, flakeStop[i].x, "*");
		i++;
		}
	}
	refresh();
	return 0;
}


/*_______________________________________________________________________________________________________________________________*/

int SNOWFLAKES(int MaxY, int MaxX, int StartStop) 
{
    int i;
	int temp = 0;
	srand(time(NULL));

	if(StartStop == 0)
	{
		system("play -q ./Music/Ending12.mp3 vol -5db&");
   		for (i = 0; i < 200; i++) 
		{
			flakeStart[i].x = (MaxX * random()) / RAND_MAX;
			flakeStart[i].y = -i; // initialisation hors de la fenêtre
		}

		while (TRUE) 
		{
    		temp = UPDATE_SNOWFLAKES(MaxY, MaxX, StartStop);
        	napms(5);
		
			if(temp == 1)
			{
				return 1;
			}
		}
	}

	else if(StartStop == 1)
	{
   		for (i = 0; i < 65; i++) 
		{
			flakeStop[i].x = (MaxX * random()) / RAND_MAX;
			flakeStop[i].y = -i; // initialisation hors de la fenêtre
		}

		while (TRUE) 
		{
    		temp = UPDATE_SNOWFLAKES(MaxY, MaxX, StartStop);
        	napms(100);
		
			if(temp == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}


/*_______________________________________________________________________________________________________________________________*/

void AFFICHAGE_PRESS_KEY(int MaxY, int MaxX)
{
	int i,j;

	for(i=0; i<MaxY; i++)
	{
		for(j=0; j<MaxX; j++)
		{
			if(i== MaxY-10 && j== MaxX/2)
			{
				mvprintw(MaxY-10,MaxX/2, "Press a Key to continue ...\n");
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void PATTERN(int MaxY, int MaxX)
{
	int i,j;

	for(i=0; i<MaxY; i++)
	{
	mvprintw(5, 10, "PATTERN");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==4 && j==4)
			{
				move(4,4);
				addch(ACS_ULCORNER);
			}
	
			if(i==4 && j>4 && j<22)
			{
				addch(ACS_HLINE);
			}

			if(i==4 && j==22)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==5 && j==4)
			{
				move(5,4);
				addch(ACS_VLINE);
			}
			
			if(i==5 && j==22)
			{
				move(5,22);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==6 && j==4)
			{
				move(6,4);
				addch(ACS_LLCORNER);
			}
		
			if(i==6 && j>4 && j<22)
			{
				addch(ACS_HLINE);
			}
	
			if(i==6 && j==22)
			{
				addch(ACS_LRCORNER);
			}
		}
	}
}

/*_______________________________________________________________________________________________________________________________*/

void REFRESH_PATTERN(int lin, int col, int FLAGTAB[lin][col])
{
	int i,j;
	int Lbase = Height+1;
	int Cbase = Length+2;
	int mvL=Lbase, mvC = Cbase;

	move(Lbase, Cbase);

	for(i=0; i<lin ; i++)
	{
		for(j=0; j<col ; j++)
		{
			if(FLAGTAB[i][j]==0)
			{
				addch(' ');
				mvC+=4;
				RRIGHT(mvL, mvC);
			}
			else if(FLAGTAB[i][j]==1)
			{
				addch(ACS_CKBOARD);
				mvaddch(mvL, mvC-1, ACS_CKBOARD);
				mvaddch(mvL, mvC+1, ACS_CKBOARD);
				mvC+=4;
				RRIGHT(mvL, mvC);
			}
			else if(FLAGTAB[i][j]==2)
			{
				attron(COLOR_PAIR(8));
				addch('X');
				mvC+=4;
				RRIGHT(mvL, mvC);
				attroff(COLOR_PAIR(8));
			}
	
			if(i<lin && j==col-1)
			{
				mvL+=2;
				mvC = Cbase;
				RJUMP(mvL, mvC);
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void SHOW_PATTERN(int lin, int col, int TAB[lin][col])
{
	REFRESH_PATTERN(lin, col, TAB); 
}


/*_______________________________________________________________________________________________________________________________*/

void VALID_CHOICE(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int ExitReplay, int dev) 
{
	int flag=0;
		
	STARS(MaxY, MaxX);

	if(ExitReplay == 1)							//après le jeu
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					flag=1;	
					clear();
					INIT_RANDOM_MODE(MaxY, MaxX, dev);
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					flag=1;
					clear();
					MENU_THEME();
					MAIN_MENU(MaxY, MaxX, dev);					
  				}
			}
		}
	}
	else if(ExitReplay == 2)						//Pour sortir du jeu pendant le jeu
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;	
					clear();
					MENU_THEME();
					MAIN_MENU(MaxY, MaxX, dev);
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;
					clear();
					RANDOM_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//Pour revenir dans le Mode Random
  				}
			}
		}
	}

	else if(ExitReplay == 6)						//Pour sortir du jeu pendant le jeu
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;	
					clear();
					MENU_THEME();
					MAIN_MENU(MaxY, MaxX, dev);
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;
					clear();
					EIFFEL_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);  //Pour revenir dans le Mode Image
  				}
			}
		}
	}

	else if(ExitReplay == 7)						//Pour sortir du jeu pendant le jeu
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;	
					clear();
					MENU_THEME();
					MAIN_MENU(MaxY, MaxX, dev);
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;
					clear();
					KYU_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//Pour revenir dans le Mode Lettre
  				}
			}
		}
	}

	else if(ExitReplay == 8)						//Pour sortir du jeu pendant le jeu
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;	
					clear();
					MENU_THEME();
					MAIN_MENU(MaxY, MaxX, dev);
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					system("pkill -n");
					flag=1;
					clear();
					SECRET_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//Pour revenir dans le Mode Secret
  				}
			}
		}
	}

	else if(ExitReplay == 3)						//Pour AFFICHER ou non le modèle
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					flag=1;	
					clear();
					SHOW_PATTERN(lin, col, TAB);
					//AFFICHAGE_PRESS_KEY(MaxY, MaxX);
					getch();
					clear();
					EIFFEL_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//quelque soit le mode image entrant on retourne dans le bon mode
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					flag=1;
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					clear();
					EIFFEL_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);		//quelque soit le mode image entrant on retourne dans le bon mode
  				}
			}
		}
	}

	else if(ExitReplay == 4)						//Pour AFFICHER ou non le modèle
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					flag=1;	
					clear();
					SHOW_PATTERN(lin, col, TAB);
					//AFFICHAGE_PRESS_KEY(MaxY, MaxX);
					getch();
					clear();
					KYU_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//quelque soit le mode lettre entrant on retourne dans le bon mode
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					flag=1;
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					clear();
					KYU_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);		//quelque soit le mode lettre entrant on retourne dans le bon mode
  				}
			}
		}
	}

	else if(ExitReplay == 5)						//Pour AFFICHER ou non le modèle
	{
		while(flag==0) 
		{

		click_souris();
	
			if (L >= MaxY/8+9 && L <= MaxY/8+11) 
			{
				if(C >= MaxX/2-14 && C <= MaxX/2-6)  
				{
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					flag=1;	
					clear();
					SHOW_PATTERN(lin, col, TAB);
					//AFFICHAGE_PRESS_KEY(MaxY, MaxX);
					getch();
					clear();
					SECRET_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//On retourne dans le mode Secret
  				}
			}
		
			if (L <= MaxY/8+11 && L >= MaxY/8+9) 
			{
				if (C >= MaxX/2+5&& C <= MaxX/2+13) 
				{
					flag=1;
					system("play -q ./Music/Menu_click.mp3 vol -12db&");
					clear();
					SECRET_MODE(lin, col, TAB, FLAGTAB, MaxY, MaxX, dev);	//On retourne dans le mode Secret
  				}
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

void EXIT_MENU(int lin, int col, int TAB[lin][col], int FLAGTAB[lin][col], int MaxY, int MaxX, int ExitReplay, int dev) 
{
	int i,j;
	clear();

	STARS(MaxY, MaxX);

	attron(A_UNDERLINE);
	if(ExitReplay == 1)
	{
		mvprintw(MaxY/8+5, MaxX/2-15,"Do you want to replay the game ?\n");				//apres le jeu
	}
	else if(ExitReplay == 2 || ExitReplay == 6 || ExitReplay == 7 || ExitReplay == 8)
	{
		mvprintw(MaxY/8+5, MaxX/2-15,"Do you want to leave the game ?\n");				//pendant le jeu
	}
	else if(ExitReplay == 3 || ExitReplay == 4 || ExitReplay == 5)
	{
		mvprintw(MaxY/8+5, MaxX/2-16,"Do you want to see the pattern ?\n");			//AFFICHER le Modèle pendant le jeu
	}
	attroff(A_UNDERLINE);

	for(i=0 ; i<MaxY ; i++)
	{
		//BOX YES
		attron(COLOR_PAIR(1));
		mvprintw(MaxY/8+10,MaxX/2-11,"YES");
		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2-14)
			{
				move(MaxY/8+9,MaxX/2-14);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}
	
			if(i==MaxY/8+9 && j==MaxX/2-6)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2-14)
			{
				move(MaxY/8+10,MaxX/2-14);
				addch(ACS_VLINE);
			}

			if(i==MaxY/8+10 && j==MaxX/2-6)
			{
				move(MaxY/8+10,MaxX/2-6);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2-14)
			{
				move(MaxY/8+11,MaxX/2-14);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2-14 && j<MaxX/2-6)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2-6)
			{
				addch(ACS_LRCORNER);
			}
		}
		attroff(COLOR_PAIR(1));
	
		//BOX NO
	attron(COLOR_PAIR(3));
		mvprintw(MaxY/8+10,MaxX/2+9,"NO");
		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+9 && j==MaxX/2+5)
			{
				move(MaxY/8+9,MaxX/2+5);
				addch(ACS_ULCORNER);
			}

			if(i==MaxY/8+9 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+9 && j==MaxX/2+13)
			{
				addch(ACS_URCORNER);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+10 && j==MaxX/2+5)
			{
				move(MaxY/8+10,MaxX/2+5);
				addch(ACS_VLINE);
			}
	
			if(i==MaxY/8+10 && j==MaxX/2+13)
			{
				move(MaxY/8+10,MaxX/2+13);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<MaxX ; j++)
		{
			if(i==MaxY/8+11 && j==MaxX/2+5)
			{
				move(MaxY/8+11,MaxX/2+5);
				addch(ACS_LLCORNER);
			}

			if(i==MaxY/8+11 && j>MaxX/2+5 && j<MaxX/2+13)
			{
				addch(ACS_HLINE);
			}

			if(i==MaxY/8+11 && j==MaxX/2+13)
			{
				addch(ACS_LRCORNER);
			}
		}
	}
	attroff(COLOR_PAIR(3));
	VALID_CHOICE(lin, col, TAB, FLAGTAB, MaxY, MaxX, ExitReplay, dev);
}


/*_______________________________________________________________________________________________________________________________*/


void RETURN_MENU_AFFICHAGE(int MaxY, int MaxX)
{
	int i,j;

	for(i=0; i<MaxY; i++)
	{
	mvprintw(1, 8, "RETURN MENU");
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==0 && j==4)
			{
				move(0,4);
				addch(ACS_ULCORNER);
			}
	
			if(i==0 && j>4 && j<22)
			{
				addch(ACS_HLINE);
			}

			if(i==0 && j==22)
			{
				addch(ACS_URCORNER);
			}
		}
	
		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==1 && j==4)
			{
				move(1,4);
				addch(ACS_VLINE);
			}
			
			if(i==1 && j==22)
			{
				move(1,22);
				addch(ACS_VLINE);
			}
		}

		for(j=0 ; j<=MaxX ; j++)
		{
			if(i==2 && j==4)
			{
				move(2,4);
				addch(ACS_LLCORNER);
			}
		
			if(i==2 && j>4 && j<22)
			{
				addch(ACS_HLINE);
			}
	
			if(i==2 && j==22)
			{
				addch(ACS_LRCORNER);
			}
		}
	}
}


/*_______________________________________________________________________________________________________________________________*/

// NON utilisé dans le jeu mais montre l'affichage en temps réel des cliques
void SHOW_FLAGTAB(int lin, int col, int FLAGTAB[lin][col])
{
	int i,j;
	int a = 20;
	
	move(a,0);
		for(i=0; i<lin; i++)
		{
			for(j=0; j<col; j++)
			{
				printw("%d ", FLAGTAB[i][j]);
			}
			printw("\n");
			a += 1;
		}
	printw("\n");
}


/*_______________________________________________________________________________________________________________________________*/

// NON utilisé dans le jeu juste pour connaitre la réponse du jeu 
void SHOW_TAB(int lin, int col, int TAB[lin][col])
{
	int i,j;
	int a = 40;
	
	move(a,0);
		for(i=0; i<lin; i++)
		{
			for(j=0; j<col; j++)
			{
				printw("%d ", TAB[i][j]);
			}
			printw("\n");
			a += 1;
		}
	printw("\n");
}



/*_______________________________________________________________________________________________________________________________*/

//FONCTION DE LANCEMENT DU JEU
void LANCEMENT_JEU()
{
	attron(A_DIM);
	int MaxX, MaxY;
	int temp = 0;
	int StartStop = 0;
	int dev = 0;				// MODE DEVELOPPEUR OFF

	REMPLISSAGE_WELCOME();
	REMPLISSAGE_CONGRATULATION();
	

	getmaxyx(stdscr, MaxY, MaxX);

	attron(COLOR_PAIR(6));
	temp = SNOWFLAKES(MaxY, MaxX, StartStop);
	attroff(COLOR_PAIR(6));

	if(temp == 1)
	{
		attron(COLOR_PAIR(5));
		AFFICHAGE_WELCOME(Welcome, MaxY, MaxX);
		attroff(COLOR_PAIR(5));
		AFFICHAGE_PRESS_KEY(MaxY, MaxX);
	
		getch();
		system("pkill play");
		clear();
		MENU_THEME();
		MAIN_MENU(MaxY, MaxX, dev);
	}
	attroff(A_DIM);
}


/*_______________________________________________________________________________________________________________________________*/

// Fonction INITIALISATION du programme 
int main() 
{
	//system("play -q Heavenless.mp3&");
	ncurses_initialiser();  //Initialisation de ncurses
	colors();  //Initialisation des couleurs 
    ncurses_souris(); //Initialisation de la souris
	LANCEMENT_JEU();
    endwin(); // Suspendre la session ncurses et restaurer le terminal
    return 0;
}

/*_______________________________________________________________________________________________________________________________*/










