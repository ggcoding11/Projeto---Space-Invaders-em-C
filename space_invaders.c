#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows

void imprimirTelaInicio();

void esconderCursor(); 

void desenharPlayer(int x);

int iniciarJogo();

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
	
	int x = 60;
	
	while (1){
		system("cls");

		desenharPlayer(x);
		
		x = lerTeclaPlayer(x);
	}
}

void desenharPlayer(int x){
	int i;
		
	//Espaço vertical
	for (i = 0; i < 20; i++){
		printf("\n");
	}
	
	//Espaço horizontal
	for (i = 0; i < x; i++){
		printf(" ");
	}
	
	printf("A");
}

int lerTeclaPlayer(int x){
	int tecla1 = _getch();
		
	if (tecla1 == 224){
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
	
	return x;
}

void esconderCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
