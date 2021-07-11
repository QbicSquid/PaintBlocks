#include <stdio.h>
#include "paintb.h"

void paint(FRAMEDATA *fData){
	int ch;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	char fileName[255] = {0};
	while(1){
		printf("%s%s\nF1-Save and Exit | F2-Exit", cls, (*fData).frameStringPTR);
		
		ch = getch();
		if(ch == 224){
			switch(getch()){
			case 72:
				if((*fData).cursorRow == 0){
					continue;
				}
				cursorMove(fData, 1);
				break;
			case 75:
				if((*fData).cursorCol == 0){
					continue;
				}
				cursorMove(fData, 2);
				break;
			case 80:
				if((*fData).cursorRow == (*fData).rows - 1){
					continue;
				}
				cursorMove(fData, 3);
				break;
			case 77:
				if((*fData).cursorCol == (*fData).cols - 1){
					continue;
				}
				cursorMove(fData, 4);
				break;
			}
		}
		else if(ch == 0){
			switch(getch()){
			case 59:
				printf("\n\nEnter the save file name:\n(File must not already exist within the program's directory and must have no spaces)\n");
				scanf("%s", &fileName);//fgets(fileName, 255, stdin);
				// call the saveFile() fuction
				cursorRem(fData);
				ch = saveFile(fData, fileName);
				if(ch != 0){
					puts("Save Failed, Returning to canvas");
					pause();
					continue;
				}
				return;
			case 60:
				printf("\nExit without saving? (Y-Yes | N-No)\n");
				ch = getch();
				if(ch == 'y' || ch =='Y'){
					return;
				}
				printf("\nReturning to canvas\n");
				pause();
				continue;
			}
		}
		else {
			switch(ch){
			case 119: //w
				if((*fData).cursorRow == 0){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow - 1, (*fData).cursorCol, 1);
				break;
			case  97: //a
				if((*fData).cursorCol == 0){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow, (*fData).cursorCol - 1, 1);
				break;
			case 115: //s
				if((*fData).cursorRow == (*fData).rows - 1){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow + 1, (*fData).cursorCol, 1);
				break;
			case 100: //d
				if((*fData).cursorCol == (*fData).cols - 1){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow, (*fData).cursorCol + 1, 1);
				break;
			case  87: //W
				if((*fData).cursorRow == 0){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow - 1, (*fData).cursorCol, 0);
				break;
			case  65: //A
				if((*fData).cursorCol == 0){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow, (*fData).cursorCol - 1, 0);
				break;
			case  83: //S
				if((*fData).cursorRow == (*fData).rows - 1){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow + 1, (*fData).cursorCol, 0);
				break;
			case  68: //D
				if((*fData).cursorCol == (*fData).cols - 1){
					continue;
				}
				blockEdit(fData, (*fData).cursorRow, (*fData).cursorCol + 1, 0);
				break;
			}
		}
	}
}
