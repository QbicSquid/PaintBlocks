#include <stdio.h>
#include "paintb.h"

int main(){
	unsigned char frameString[8500];
	
	FRAMEDATA fData;
	fData.frameStringPTR = frameString;
	fData.cursorCol = 0;
	fData.cursorRow = 0;
	fData.cursorMem = ' ';
	
	char fileName[255];
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	int ch;
	
	while(1){
		printf("%s___Paint Blocks(v0.4.2 beta)___\n\n\n1) New\n2) Load\n3) Help\n\n>> ", cls);
		ch = getch();
		printf("%c\n\n", ch);
		if(ch == '1'){
			while(1){
				printf("\n\nEnter Canvas Dimentions: \nrows(0<   <=50):\n");
				scanf("%d", &fData.rows);
				if(fData.rows < 1 || fData.rows > 50){
					continue;
				}
				printf("\nColumns(0<   <=160:)\n");
				scanf("%d", &fData.cols);
				if(fData.cols < 1 || fData.cols > 160){
					continue;
				}
				
				initNewCanvas(&fData);
				break;
			}
		}
		else if(ch == '2'){
			printf("\n\n\nEnter File Name:\n(File must be in the same directory as the program and must have no spaces)\n\n");
			scanf("%s", fileName);
			
			ch = loadFile(&fData, fileName); // loading framestring
			if(ch < 0){ // if framestring was not loaded properly
				return -1;
			}
			
			fData.rows = ch % 100;
			fData.cols = (ch - fData.rows) / 100;
			printf("checking -> %d %d\n", fData.rows, fData.cols);//debugging line
			cursorAdd(&fData);
		}
		else if(ch == '3'){
			printf("%sHelp\n\n", cls);
			printf("> Use arrow keys to move cursor\n");
			printf("> Use WASD to place paint blocks\n");
			printf("> Use Shift/CapsLock + WASD to erase paint blocks\n\n");
			pause();
			continue;
		}
		else{
			continue;
		}
	
	paint(&fData);
	}
	
	return 0;
}
