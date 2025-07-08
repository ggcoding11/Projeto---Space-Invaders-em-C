#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows

void imprimirTelaInicio();

void esconderCursor(); 

void desenhar(int x, int y, char a);

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
	int y = 20;
	
	while (1){
		system("cls");

		desenhar(x, y, 'A');
		
		x = lerTeclaPlayer(x);
		
		Sleep(20);
	}
}

void desenhar(int x, int y, char a){
	int i;

	//Espaço vertical
	for (i = 0; i < y; i++){
		printf("\n");
	}
	
	//Espaço horizontal
	for (i = 0; i < x; i++){
		printf(" ");
	}
	
	printf("%c", a);
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
