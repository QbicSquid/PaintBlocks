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
			case 63:
				clip(fData);
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

void clip(FRAMEDATA *fData){
	int ch;
	int clipExit = 0;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	cursorRem(fData);
	ch = -1;
	do{
		ch++;
		(*fData).frameStringBUPTR[ch] = (*fData).frameStringPTR[ch];
	} while ((*fData).frameStringPTR[ch] != '\0');
	cursorRestore(fData);
	
	while(1){
		printf("%s%s\nF1-Copy | F2-Return", cls, (*fData).frameStringPTR);
		
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
			case 59: // copy and return to paint function
					// copy(fData) function
					printf("\n Copy successful\n");
					clipExit = 1;
					pause();
					break;
			case 60: // return to paint funtion
				printf("\n Copy cancelled\n");
				clipExit = 1;
				pause();
				break;
			}
		}
		else {
			switch(ch){
			case 119: //w
				if((*fData).cursorRow == 0){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow - 1, (*fData).cursorCol, 1);
				break;
			case  97: //a
				if((*fData).cursorCol == 0){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow, (*fData).cursorCol - 1, 1);
				break;
			case 115: //s
				if((*fData).cursorRow == (*fData).rows - 1){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow + 1, (*fData).cursorCol, 1);
				break;
			case 100: //d
				if((*fData).cursorCol == (*fData).cols - 1){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow, (*fData).cursorCol + 1, 1);
				break;
			case  87: //W
				if((*fData).cursorRow == 0){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow - 1, (*fData).cursorCol, 0);
				break;
			case  65: //A
				if((*fData).cursorCol == 0){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow, (*fData).cursorCol - 1, 0);
				break;
			case  83: //S
				if((*fData).cursorRow == (*fData).rows - 1){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow + 1, (*fData).cursorCol, 0);
				break;
			case  68: //D
				if((*fData).cursorCol == (*fData).cols - 1){
					continue;
				}
				clipBlockEdit(fData, (*fData).cursorRow, (*fData).cursorCol + 1, 0);
				break;
			}
		}
	
		if(clipExit == 1){
			cursorRem(fData);
			ch = -1;
			do{
				ch++;
				(*fData).frameStringPTR[ch] = (*fData).frameStringBUPTR[ch];
			} while ((*fData).frameStringBUPTR[ch] != '\0');
			cursorRestore(fData);
			
			return;
		}
	}
}

void clipBlockEdit(FRAMEDATA *fData, int blockRow, int blockCol, int key){
	int blockID;
	blockID = (blockRow + 1) * ((*fData).cols + 3) + (blockCol + 1);
	
	switch(key){
		case 0:
			(*fData).frameStringPTR[blockID] = (*fData).frameStringBUPTR[blockID];
			break;
		case 1:
			(*fData).frameStringPTR[blockID] = 197;
			break;
	}
}

void copy(FRAMEDATA *fData){
	int i, j, blockID;
	int rowsTop = -1, rowsBot = -1;
	int colsLeft = -1, colsRight = -1;
	
	//selecting the rectangular area to copy
	for(i = 0; i < (*fData).rows; i++){ // scanning from top to botton
		for(j = 0; j < (*fData).cols; j++){
			blockID = (i + 1) * ((*fData).cols + 3) + (j + 1);
			if((*fData).frameStringBUPTR[blockID] == 197){
				rowsTop = i;
				break;
			}
		}
		if(rowsTop > -1){
			break;
		}
	}
	
	for(i = (*fData).rows - 1; i > 0; i--){ // scanning from bottom to top
		for(i = 0; i < (*fData).cols; i++){
			blockID = (i + 1) * ((*fData).cols + 3) + (j + 1);
			if((*fData).frameStringBUPTR[blockID] == 197){
				rowsBot = i;
				break;
			}
		}
		if(rowsBot > -1){
			break;
		}
	}
	
}

//select function -- done, clip()

//copy function -- in progress

//paste function

//undo+redo paste function

// "good selection" checker to stop users for doing bad crops

/*
the clipboard consists of 2 memory blocks
1) contains the copied block
2) contains th data in the block that the paste function
	pasted onto. To be used by the undo unction.
*/
