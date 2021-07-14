#include <stdio.h>
#include "paintb.h"


void paint(FRAMEDATA *fData){
	int ch;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
	\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	char fileName[255] = {0};
	while(1){
		printf("%s%s\nF1-Save and Exit | F2-Exit | F5-Copy | F6-Paste", cls, (*fData).frameStringPTR);
		
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
					cursorRestore(fData);
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
				clipUp(fData);
				continue;
			case 64:
				if((*fData).clipRows == -99){
					printf("\nNo copied data found\n");
					pause();
					continue;
				}
				clipDown(fData);
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

void clipUp(FRAMEDATA *fData){
	int ch;
	int clipExit = 0;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
	\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

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
			case 59: // copy and go to clipDown function
					copy(fData);
					clipExit = 1;
					break;
			case 60: // return to paint funtion
				clipExit = 1;
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
			
//			clipDown(fData);
			
			return;
		}
	}
}

void copy(FRAMEDATA *fData){
	int i, j, k, blockID;
	int rowsTop = -1, rowsBottom = -1;
	int colsLeft = -1, colsRight = -1;
	
	//selecting the rectangular area to copy
	for(i = 0; i < (*fData).rows; i++){ // scanning from top to botton
		for(j = 0; j < (*fData).cols; j++){
			blockID = (i + 1) * ((*fData).cols + 3) + (j + 1);
			if((*fData).frameStringPTR[blockID] == 197){
				rowsTop = i;
				break;
			}
		}
		if(rowsTop > -1){
			break;
		}
	}
	
	for(i = (*fData).rows - 1; i > -1; i--){ // scanning from bottom to top
		for(j = 0; j < (*fData).cols; j++){
			blockID = (i + 1) * ((*fData).cols + 3) + (j + 1);
			if((*fData).frameStringPTR[blockID] == 197){
				rowsBottom = i;
				break;
			}
		}
		if(rowsBottom > -1){
			break;
		}
	}
	
	for(i = 0; i < (*fData).cols; i++){ // scanning from left to right
		for(j = 0; j < (*fData).rows; j++){
			blockID = (j + 1) * ((*fData).cols + 3) + (i + 1);
			if((*fData).frameStringPTR[blockID] == 197){
				colsLeft = i;
				break;
			}
		}
		if(colsLeft > -1){
			break;
		}
	}
	
	for(i = (*fData).cols - 1; i > -1; i--){ // scanning from right to left
		for(j = 0; j < (*fData).rows; j++){
			blockID = (j + 1) * ((*fData).cols + 3) + (i + 1);
			if((*fData).frameStringPTR[blockID] == 197){
				colsRight = i;
				break;
			}
		}
		if(colsRight > -1){
			break;
		}
	}
	
	(*fData).clipRows = rowsBottom - rowsTop + 1;
	(*fData).clipCols = colsRight - colsLeft + 1;
	
	k = 0;
	for(i = rowsTop; i < rowsBottom + 1; i++){
		for(j = colsLeft; j < colsRight + 1; j++){
			blockID = (i + 1) * ((*fData).cols + 3) + (j + 1);
			
			if((*fData).frameStringPTR[blockID] == 197){
				(*fData).clipStringPTR[k] = (*fData).frameStringBUPTR[blockID];
				k++;
			}
			else{
				(*fData).clipStringPTR[k] = 146;
				k++;
			}
		}
	}
}

void clipDown(FRAMEDATA *fData){
	int i, ch;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
	\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	int clipPosRow = (*fData).cursorRow; //
	int clipPosCol = (*fData).cursorCol; // position of the clip to be pasted
	cursorRem(fData);
	
	while(1){
		i = -1;
		do{ // loading the framstring backup into the framestring
			i++;
			(*fData).frameStringPTR[i] = (*fData).frameStringBUPTR[i];
		} while ((*fData).frameStringBUPTR[i] != '\0');
		
		//adding the clipboard onto the frameString
		paste(fData, clipPosRow, clipPosCol);
		
		printf("%s%s\nF1-Paste and return| F2-Return | F3-Prview original", cls, (*fData).frameStringPTR);
		
		//selection
		ch = getch();
		if(ch == 224){
			switch(getch()){
			case 72:
				if(clipPosRow < 2 - (*fData).clipRows){
					continue;
				}
				clipPosRow--;
				break;
			case 75:
				if(clipPosCol < 2 - (*fData).clipCols){
					continue;
				}
				clipPosCol--;
				break;
			case 80:
				if((*fData).rows - 2 < clipPosRow){
					continue;
				}
				clipPosRow++;
				break;
			case 77:
				if((*fData).cols - 2 < clipPosCol){
					continue;
				}
				clipPosCol++;
				break;
			}
		}
		else if(ch == 0){
			switch(getch()){
			case 59:
				// paste and exit
				i = -1;
				do{ // loading the framStringBU into the undoString
					i++;
					(*fData).undoStringPTR[i] = (*fData).frameStringBUPTR[i];
				} while ((*fData).frameStringBUPTR[i] != '\0');
				
				i = -1;
				do{ // loading the framString into the frameStringBU
					i++;
					(*fData).frameStringBUPTR[i] = (*fData).frameStringPTR[i];
				} while ((*fData).frameStringBUPTR[i] != '\0');
				
				cursorRestore(fData);
				return;
			case 60:
				// exit
				
				i = -1;
				do{ // loading the framStringBU into the undoString
					i++;
					(*fData).frameStringPTR[i] = (*fData).frameStringBUPTR[i];
				} while ((*fData).frameStringBUPTR[i] != '\0');
				
				cursorRestore(fData);
				return;
			case 61:
				// add a "preview original framestring" function here
				printf("%s%s\n", cls, (*fData).frameStringBUPTR);
				pause();
				continue;
			}
		}	
	}
}

void paste(FRAMEDATA *fData, int clipPosRow, int clipPosCol){
	int i, j, k;
	int row,col;
	int blockID;
	
	k = 0;
	for(i = 0; i < (*fData).clipRows; i++){
		for(j = 0; j < (*fData).clipCols; j++){
			row = clipPosRow + i;
			col = clipPosCol + j;
			
			//checking for out of boudns
			if(-1 < row && row < (*fData).rows && -1 < col && col < (*fData).cols){
				blockID = (row + 1) * ((*fData).cols + 3) + (col + 1);
				
				if((*fData).clipStringPTR[k] != 146){ // checking for null character
					(*fData).frameStringPTR[blockID] = (*fData).clipStringPTR[k]; // pasting the block
				}
			}
			
			k++;
		}
	}
	
	/*
	gives the top left block of the copied blocks position(row, coluwm) that is relative to the (0, 0) position.
	these coordinates may be negative, but at least one block in the block must have a valid position within the canvas at all times.
	NOTE that positions of all blocks aren't generated. Instead the valid range of positions of the top left block is calculated.
	*/
}

void undo(FRAMEDATA *fData){
	
}
//select function -- done, clip()

//copy function -- done, copy()

//paste function -- done, paste()

//undo+redo paste function

// "good selection" checker to stop users for doing bad crops -- no need, found a workaround

/*
the clipboard consists of 2 memory blocks
1) contains the copied block
2) contains th data in the block that the paste function
	pasted onto. To be used by the undo unction.
*/
