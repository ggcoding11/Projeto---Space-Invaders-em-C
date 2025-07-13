#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows

#define LINHAS 20
#define COLUNAS 30

#define LINHASENEMY 1
#define COLUNASENEMY 1

void imprimirTelaInicio();
void esconderCursor(); 
void inicializarMapa(int *turnoMoveEnemy); //Esse vai criar a matriz  e definir as posições de todos, vai servir de base pro desenhar
void desenharMapa(); // Esse vai desenhar cada quadro do jogo, então pra movimentar algo, basta eu trocar o espaço no vetor, o resto se desenha sozinho
void lerTeclaPlayer();
int iniciarJogo();

char mapa[LINHAS][COLUNAS];

int matrizEnemy[LINHASENEMY][COLUNASENEMY];

int xPlayer = 15;
int xTiro, yTiro;
int xEnemyInicio = 2;
int yEnemyInicio = 0;

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
	
	int i, j;
	
	for (i = 0; i < LINHASENEMY; i++){
		for (j = 0; j < COLUNASENEMY; j++){
			matrizEnemy[i][j] = 1;
		}
	}
	
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
	
	//Verificação das colunas limites
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
	
	if (*turnoMoveEnemy == 9){
		int xLimiteMapa = COLUNAS - 1;
		int xInicioMapa = 1;
		
		if ((xEnemyInicio + colLimiteDireita == xLimiteMapa - 1) && (andarDireita)){
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
		
		*turnoMoveEnemy = 0;	
	}	
	
	//Posicionamento do player
	mapa[LINHAS - 1][xPlayer] = 'A'; 
	
	//Se o player atirou, fazer animação até o tiro sumir, aí libera o próximo
	if (atirou){
		//Considerando que o tiro esteja na área dos inimigos, eu vou tirar os espaçamentos 
		//do xEnemyInicio e do yEnemyInicio e ver como está na matrizEnemy
		
		//E basicamente a lógica do posicionamento de inimigos, mas ao contrário
		int relX = xTiro - xEnemyInicio;
		int relY = yTiro - yEnemyInicio;
		
		if ((relX >= 0 && relX < COLUNASENEMY) && (relY >= 0 && relY < LINHASENEMY) && (matrizEnemy[relY][relX])){
			matrizEnemy[relY][relX] = 0;
			atirou = 0;
		} else {
			mapa[yTiro][xTiro] = '^';
		
			yTiro--;
			
			if (yTiro < 0){
				atirou = 0;
			}	
		}	
	}
	
	//Posicionamento dos inimigos
	for (i = 0; i < LINHASENEMY; i++){
		for (j = 0; j < COLUNASENEMY; j++){
			if (matrizEnemy[i][j]){
				mapa[yEnemyInicio + i][xEnemyInicio + j] = 'M';
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
