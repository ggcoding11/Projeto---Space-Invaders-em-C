#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows
#include <stdlib.h>
#include <time.h>

#define LINHAS 15
#define COLUNAS 30

#define LINHASENEMY 3
#define COLUNASENEMY 18

#define VELTIROPLAYER 1
#define VELTIROENEMY 5

#define VELENEMY 18

void imprimirTelaInicio();
void imprimirTelaMorte();
void imprimirTelaVitoria();
void esconderCursor(); 
void inicializarInimigos();
void inicializarMapa(); //Esse vai criar a matriz  e definir as posições de todos, vai servir de base pro desenhar
void construirArena();
void configurarMovimentoEnemy();
void configurarTirosPlayer();
void configurarTirosEnemy();
void verificarVitoria();
void posicionarInimigos();
void desenharMapa(); // Esse vai desenhar cada quadro do jogo, então pra movimentar algo, basta eu trocar o espaço no vetor, o resto se desenha sozinho
void lerTeclaPlayer();
int iniciarJogo();

char mapa[LINHAS][COLUNAS];

int matrizEnemy[LINHASENEMY][COLUNASENEMY];

int xPlayer, yPlayer ;
int xTiro, yTiro;
int xTiroEnemy, yTiroEnemy;
int xEnemyInicio, yEnemyInicio;

int atirouPlayer, atirouEnemy;

int andarDireita;

int contadorTurnos;

int morreu, venceu;

int main(){
	srand(time(NULL));
	
	imprimirTelaInicio();
	
	int tecla;
	
	do {
		tecla = _getch(); 
	} while (tecla != 13);
	
	do {
		iniciarJogo();
		
		system("cls");
		
		if (morreu) {
			imprimirTelaMorte();
			
			do {
				tecla = _getch();
			} while ((tecla != 83) && (tecla != 115) && (tecla != 78) && (tecla != 110));
		}
		
		if (venceu) {
			imprimirTelaVitoria();
		}
	} while ((!venceu) && (morreu && ((tecla == 83 || tecla == 115))));

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

void imprimirTelaMorte(){
	int i, j;
	
	for (i = 0; i < 50; i++){
		printf("-");
	}
	
	printf("\n");
	
	for (i = 0; i < 5; i++){
		printf("|");
		
		if (i == 2){
			for (j = 0; j < 19; j++){
				printf(" ");
			}
			
			printf("FIM DE JOGO");
			
			for (j = 0; j < 18; j++){
				printf(" ");
			}
		} else {
			if (i == 3){
				for (j = 0; j < 14; j++){
					printf(" ");
				}
				
				printf("Deseja continuar? [S/N]");
				
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

void imprimirTelaVitoria(){
	int i, j;
	
	for (i = 0; i < 50; i++){
		printf("-");
	}
	
	printf("\n");
	
	for (i = 0; i < 5; i++){
		printf("|");
		
		if (i == 2){
			for (j = 0; j < 19; j++){
				printf(" ");
			}
			
			printf("VOCE VENCEU!");
			
			for (j = 0; j < 17; j++){
				printf(" ");
			}
		} else {
			if (i == 3){
				for (j = 0; j < 13; j++){
					printf(" ");
				}
				
				printf("Muito obrigado por jogar");
				
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
	morreu = 0;
	venceu = 0;
	
	xPlayer = 15;
	yPlayer = LINHAS - 1;
	xEnemyInicio = 2;
	yEnemyInicio = 0;
	
	atirouPlayer = 0;
	atirouEnemy = 0;
	
	andarDireita = 1;
	
	contadorTurnos = 0;
	
	esconderCursor();
	
	inicializarInimigos();
		
	do {
		system("cls");
	
		inicializarMapa();
		
		desenharMapa();
		
		lerTeclaPlayer();
		
		contadorTurnos++;
	} while (!morreu && !venceu);
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
		
	construirArena();
	
	configurarMovimentoEnemy();
	
	configurarTirosPlayer();
	configurarTirosEnemy();
	
	posicionarInimigos();
	
	verificarVitoria();
	
	mapa[yPlayer][xPlayer] = 'A'; 
}

void construirArena(){
	int i,j;
	
	for (i = 0; i < LINHAS; i++){
		for (j = 0; j < COLUNAS; j++){
			if ((j == 0) || (j == COLUNAS - 1)){
				mapa[i][j] = '|';
			} else {
				mapa[i][j] = ' ';	
			}
		}	
	}
}

void configurarMovimentoEnemy(){
	int i, j;
	
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
	
	int relX = xPlayer - xEnemyInicio;
	int relY = yPlayer - yEnemyInicio;
	
	if ((relX >= 0 && relX < COLUNASENEMY) && (relY >= 0 && relY < LINHASENEMY) && (matrizEnemy[relY][relX])){
		morreu = 1;
	}
}

void configurarTirosPlayer(){
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
}

void configurarTirosEnemy(){
	if ((contadorTurnos > 0) && (!atirouEnemy)){
		int linhaAtirador;
		int colAtirador;
		
		int encontrou = 0;
		
		do {
			linhaAtirador = yEnemyInicio + (LINHASENEMY - 1);
			colAtirador = xEnemyInicio + (rand() % COLUNASENEMY);
			
			while (linhaAtirador >= yEnemyInicio && matrizEnemy[linhaAtirador - yEnemyInicio][colAtirador - xEnemyInicio] == 0){
				linhaAtirador--;
			}	
			
			if (matrizEnemy[linhaAtirador - yEnemyInicio][colAtirador - xEnemyInicio] == 1){
				encontrou = 1;
			}
		} while (!encontrou);
		
		yTiroEnemy = linhaAtirador + 1;
		xTiroEnemy = colAtirador; 
		
		atirouEnemy = 1;
	}
	
	if (atirouEnemy){
		if ((atirouPlayer) && (xTiro == xTiroEnemy) && (yTiro == yTiroEnemy)){
			mapa[yTiro][xTiro] = 'X';
			
			atirouPlayer = 0;
			atirouEnemy = 0;
		} else {
			if ((xPlayer == xTiroEnemy) && (yPlayer == yTiroEnemy)){
				morreu = 1;
			} else {
				mapa[yTiroEnemy][xTiroEnemy] = 'o';
		
				if (contadorTurnos % VELTIROENEMY == 0){
					yTiroEnemy++;
					
					if (yTiroEnemy == LINHAS){
						atirouEnemy = 0;
					}	
				}	
			}	
		}
	}
}

void posicionarInimigos(){
	int i, j;
	
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

void verificarVitoria(){
	int i, j;
	
	int vivo = 0;
	
	for (i = 0; i < LINHASENEMY; i++){
		for (j = 0; j < COLUNASENEMY; j++){
			if (matrizEnemy[i][j]){
			   	vivo = 1;   
				
				break;
			}		
		}
	}
	
	if (!vivo){
		venceu = 1;
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
