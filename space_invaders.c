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
			
		for (j = 1; j < 49; j++){
			
			printf(" ");
		} 
		
		printf("|\n");
	}
	
	for (i = 0; i < 50; i++){
		printf("-");
	}

	return 0;
}

