#include <stdio.h>
#include <conio.h> //S� pro windows man�
#include <windows.h> //Tamb�m s� pra windows

#define LINHAS 20
#define COLUNAS 30

void imprimirTelaInicio();

void esconderCursor(); 

void inicializarMapa(int *turnoMoveEnemy); //Esse vai criar a matriz  e definir as posi��es de todos, vai servir de base pro desenhar

void desenharMapa(); // Esse vai desenhar cada quadro do jogo, ent�o pra movimentar algo, basta eu trocar o espa�o no vetor, o resto se desenha sozinho

void lerTeclaPlayer();

int iniciarJogo();

char mapa[LINHAS][COLUNAS];

int xPlayer = 15;
int xTiro, yTiro;
int xEnemy = 2;
int yEnemy = 0;

int atirou = 0;

int andarDireita = 1;

int main(){
	imprimirTelaInicio();
	
	int tecla;
	
	do {
		tecla = _getch();
	} while (tecla != 13);
	
	iniciarJogo();

	return 0;
}

void imprimirTelaInicio(){
	int i, j;
	
	for (i = 0; i < 50; i++){
		printf("-");
	}
	
	printf("\n");
	
	for (i = 0; i < 5; i++){
		printf("|");
		
		if (i == 2){
			for (j = 0; j < 10; j++){
				printf(" ");
			}
			
			printf("SPACE INVADERS - Por Mr. JeeJ");
			
			for (j = 0; j < 9; j++){
				printf(" ");
			}
		} else {
			if (i == 3){
				for (j = 0; j < 12; j++){
					printf(" ");
				}
				
				printf("Aperte ENTER para comecar");
				
				for (j = 0; j < 11; j++){
					printf(" ");
				}	
			} else {
				for (j = 1; j < 49; j++){		
					printf(" ");
				}
			}		 	
		}
			
		printf("|\n");
	}
	
	for (i = 0; i < 50; i++){
		printf("-");
	}
}

int iniciarJogo(){
	esconderCursor();
	
	int turnoMoveEnemy = 0;
	
	while (1){
		system("cls");
	
		inicializarMapa(&turnoMoveEnemy);
		
		desenharMapa();
		
		lerTeclaPlayer();
		
		Sleep(80);
		
		turnoMoveEnemy++;
	}
}

void inicializarMapa(int *turnoMoveEnemy){
	int i,j;
	
	//Limpeza geral do mapa antes de preencher
	for (i = 0; i < LINHAS; i++){
		for (j = 0; j < COLUNAS; j++){
			if ((j == 0) || (j == COLUNAS - 1)){
				mapa[i][j] = '|';
			} else {
				mapa[i][j] = ' ';	
			}
		}	
	}
	
	if (*turnoMoveEnemy == 9){
		int xLastEnemy = xEnemy + 19;
		int xLimiteMapa = COLUNAS - 1;
		int xInicioMapa = 1;
		
		if ((xLastEnemy == xLimiteMapa - 1) && (andarDireita)){
			andarDireita = 0;
			yEnemy++;
		} else {
			if ((xEnemy == xInicioMapa) && (!andarDireita)){
				andarDireita = 1;
				yEnemy++;
			} else {
				if (andarDireita){
					xEnemy++;
				} else {
					xEnemy--;
				}
			}
		}
		
		*turnoMoveEnemy = 0;	
	}	
	
	//Posicionamento dos inimigos
	for (i = yEnemy; i < yEnemy + 5; i++){
		for (j = xEnemy; j < xEnemy + 20; j++){
			mapa[i][j] = 'M';
		}
	}	
	
	//Posicionamento do player
	mapa[LINHAS - 1][xPlayer] = 'A'; 
	
	
	//Se o player atirou, fazer anima��o at� o tiro sumir, a� libera o pr�ximo
	if (atirou){
		mapa[yTiro][xTiro] = '^';
		
		yTiro--;
		
		if (yTiro < 0){
			atirou = 0;
		}
	}
}

void desenharMapa(){
	int i, j;
	
	for (i = 0; i < LINHAS; i++){
		for (j = 0; j < COLUNAS; j++){
			printf("%c ", mapa[i][j]);
		}
		
		printf("\n");
	}
}

void lerTeclaPlayer(){
	if (kbhit()){
		int tecla1 = _getch();
		
		switch(tecla1){
			case 122:
			case 90:
				if (!atirou){
					atirou = 1;
					
					xTiro = xPlayer;
					yTiro = LINHAS - 2;	
				}	
			break;
			
			case 224:{
				int tecla2 = _getch();
			
				switch (tecla2){
					case 75:
						if (xPlayer != 1){
							xPlayer--;
						}
					break;
					
					case 77:
						if (xPlayer != COLUNAS - 2){
							xPlayer++;
						}
					break;
				}
			}
			
			break;
		}
	}
}

void esconderCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
