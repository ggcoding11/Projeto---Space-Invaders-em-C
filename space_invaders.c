#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows

#define LINHAS 40
#define COLUNAS 40

void imprimirTelaInicio();

void esconderCursor(); 

void inicializarMapa(); //Esse vai criar a matriz

void desenharMapa(); // Esse vai desenhar cada quadro do jogo, então pra movimentar algo, basta eu trocar o espaço no vetor, o resto se desenha sozinho

int iniciarJogo();

char mapa[LINHAS][COLUNAS];

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
	
	inicializarMapa();
	
	int x = 60;
	int y = 20;
	
	while (1){
		system("cls");
		
		x = lerTeclaPlayer(x);
		
		Sleep(20);
	}
}

void inicializarMapa(){
	int i,j;
	
	for (i = 0; i < LINHAS; i++){
		for (j = 0; j < COLUNAS; j++){
			mapa[i][j] = ' ';
		}	
	}
}

int lerTeclaPlayer(int x){
	if (kbhit()){
		int tecla1 = _getch();
		
		switch(tecla1){
			case 122:
			case 90:
				
			break;
			
			case 224:{
				int tecla2 = _getch();
			
				switch (tecla2){
					case 75:
						x--;
					break;
					
					case 77:
						x++;
					break;
				}
			}
			
			break;
		}
	}
	
	return x;
}

void esconderCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
