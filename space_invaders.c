#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows
#include <stdlib.h>
#include <time.h>

#define LINHAS 15
#define COLUNAS 30

#define LINHASENEMY 4
#define COLUNASENEMY 18

#define VELTIROPLAYER 6
#define VELTIROENEMY 8

#define VELENEMY 40

void imprimirTelaInicio();
void esconderCursor(); 
void inicializarInimigos();
void inicializarMapa(); //Esse vai criar a matriz  e definir as posições de todos, vai servir de base pro desenhar
void desenharMapa(); // Esse vai desenhar cada quadro do jogo, então pra movimentar algo, basta eu trocar o espaço no vetor, o resto se desenha sozinho
void lerTeclaPlayer();
int iniciarJogo();

char mapa[LINHAS][COLUNAS];

int matrizEnemy[LINHASENEMY][COLUNASENEMY];

int xPlayer = 15;
int xTiro, yTiro;
int xTiroEnemy, yTiroEnemy;
int xEnemyInicio = 2;
int yEnemyInicio = 0;

int atirouPlayer = 0;
int atirouEnemy = 0;

int andarDireita = 1;

int contadorTurnos = 0;

int main(){
	srand(time(NULL));
	
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
	
	inicializarInimigos();
		
	while (1){
		system("cls");
	
		inicializarMapa();
		
		desenharMapa();
		
		lerTeclaPlayer();
		
		contadorTurnos++;
	}
}

void inicializarInimigos(){
	int i, j;
	
	for (i = 0; i < LINHASENEMY; i++){
		for (j = 0; j < COLUNASENEMY; j++){
			matrizEnemy[i][j] = 1;
		}
	}
}

void inicializarMapa(){
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
	
	//Verificação das colunas limites para a colisão dos inimigos no limite do mapa
	int achouLimite = 0;
	int colLimiteDireita = COLUNASENEMY - 1;
	
	while (!achouLimite){
		
		j = colLimiteDireita;
		
		while (j >= 0 && !achouLimite){
			i = 0;
			
			while (i < LINHASENEMY && !achouLimite){
				if (matrizEnemy[i][j]){
					achouLimite = 1;
					colLimiteDireita = j;
				}	
				
				i++;	
			}
			
			j--;	
		}
	}
	
	achouLimite = 0;
	int colLimiteEsquerda = 0;
	
	while (!achouLimite){
		
		j = 0;
		
		while (j < COLUNASENEMY && !achouLimite){
			i = 0;
			
			while (i < LINHASENEMY && !achouLimite){
				if (matrizEnemy[i][j]){
					achouLimite = 1;
					colLimiteEsquerda = j;
				}	
				
				i++;	
			}
			
			j++;	
		}
	}
	
	if (contadorTurnos % VELENEMY == 0){
		int xLimiteMapa = COLUNAS - 2;
		int xInicioMapa = 1;
		
		if ((xEnemyInicio + colLimiteDireita == xLimiteMapa) && (andarDireita)){
			andarDireita = 0;
			yEnemyInicio++;
		} else {
			if ((xEnemyInicio + colLimiteEsquerda == xInicioMapa) && (!andarDireita)){
				andarDireita = 1;
				yEnemyInicio++;
			} else {
				if (andarDireita){
					xEnemyInicio++;
				} else {
					xEnemyInicio--;
				}
			}
		}
	}	
	
	//Posicionamento do player
	mapa[LINHAS - 1][xPlayer] = 'A'; 
	
	//Se o player atirouPlayer, fazer animação até o tiro sumir, aí libera o próximo
	if (atirouPlayer){
		int relX = xTiro - xEnemyInicio;
		int relY = yTiro - yEnemyInicio;
		
		if ((relX >= 0 && relX < COLUNASENEMY) && (relY >= 0 && relY < LINHASENEMY) && (matrizEnemy[relY][relX])){
			matrizEnemy[relY][relX] = 2;
			atirouPlayer = 0;
		} else {
			mapa[yTiro][xTiro] = '^';
			
			if (contadorTurnos%VELTIROPLAYER == 0){
				yTiro--;	
			}
	
			if (yTiro < 0){
				atirouPlayer = 0;
			}	
		}	
	}
	
	if ((contadorTurnos > 0) && (contadorTurnos % 46 == 0) && (!atirouEnemy)){
		int linhaAtirador = yEnemyInicio + (LINHASENEMY - 2);
		int colAtirador;
		
		int encontrou = 0;
		
		do {
			colAtirador = xEnemyInicio + (rand() % COLUNASENEMY);
			
			while (linhaAtirador >= 0 && matrizEnemy[linhaAtirador][colAtirador] == 0){
				linhaAtirador--;
			}	
			
			if (matrizEnemy[linhaAtirador][colAtirador]){
				encontrou = 1;
			}
		} while (!encontrou);
		
		yTiroEnemy = linhaAtirador + 1;
		xTiroEnemy = colAtirador; 
		
		atirouEnemy = 1;
	}
	
	if (atirouEnemy){
		mapa[yTiroEnemy][xTiroEnemy] = 'o';
	
		if (contadorTurnos % VELTIROENEMY == 0){
			yTiroEnemy++;
			
			if (yTiroEnemy == LINHAS){
				atirouEnemy = 0;
			}	
		}
	}
	
	//Posicionamento dos inimigos
	for (i = 0; i < LINHASENEMY; i++){
		for (j = 0; j < COLUNASENEMY; j++){
			switch (matrizEnemy[i][j]){
				case 1:
					mapa[yEnemyInicio + i][xEnemyInicio + j] = 'M';
				break;
				
				case 2:
					mapa[yEnemyInicio + i][xEnemyInicio + j] = 'X';
					matrizEnemy[i][j] = 0;
				break;
			}
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
				if (!atirouPlayer){
					atirouPlayer = 1;
					
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
