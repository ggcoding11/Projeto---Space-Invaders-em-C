#include <stdio.h>
#include <conio.h> //Só pro windows mané
#include <windows.h> //Também só pra windows

void imprimirTelaInicio();

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
	int tecla1, tecla2;

	while (1){
		system("cls");
		
		tecla1 = _getch();
		
		if (tecla1 == 224){
			tecla2 = _getch();
			
			switch (tecla2){
				case 75:
					printf("Apertou Esquerda\n");
				break;
				
				case 77:
					printf("Apertou Direita\n");
				break;
			}
		}
		
		printf("A");
		
		Sleep(2000);
	}
	
	
}

