#include <stdio.h>
#include <windows.h>

int main(){
	int y = 20;
	
	int i;
	
	while (y){
		system("cls");
	
		for (i = 0; i < y; i++){
			printf("\n");
		}
		
		printf("^");
		
		
		y--;
		
		Sleep(200);	
	}

	return 0;
}

