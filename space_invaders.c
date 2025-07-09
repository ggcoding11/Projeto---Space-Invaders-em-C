#include <stdio.h>
#include <conio.h> //S� pro windows man�
#include <windows.h> //Tamb�m s� pra windows

#define LINHAS 20
#define COLUNAS 60

void imprimirTelaInicio();

void esconderCursor(); 

void inicializarMapa(); //Esse vai criar a matriz  e definir as posi��es de todos, vai servir de base pro desenhar

void desenharMapa(); // Esse vai desenhar cada quadro do jogo, ent�o pra movimentar algo, basta eu trocar o espa�o no vetor, o resto se desenha sozinho

void lerTeclaPlayer();

int iniciarJogo();

char mapa[LINHAS][COLUNAS];

int xPlayer = 30;
int xTiro, yTiro;

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
	
	while (1){
		system("cls");
	
		inicializarMapa();
		
		desenharMapa();
		
		lerTeclaPlayer();
		
		Sleep(20);
	}
}

void inicializarMapa(){
	int i,j;
	
	//REINICIO PADR�O DO MAPA
	for (i = 0; i < LINHAS; i++){
		for (j = 0; j < COLUNAS; j++){
			mapa[i][j] = ' ';
		}	
	}
	
	//POSICIONAMENTO DO PLAYER
	mapa[LINHAS - 1][xPlayer] = 'A'; 
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
				//Atirou!!
			break;
			
			case 224:{
				int tecla2 = _getch();
			
				switch (tecla2){
					case 75:
						if (xPlayer != 0){
							xPlayer--;
						}
					break;
					
					case 77:
						if (xPlayer != COLUNAS - 1){
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
