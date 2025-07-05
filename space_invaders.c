#include <stdio.h>

int main(){
	int i;
	int j;
	
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

	return 0;
}

