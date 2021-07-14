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

void clipUp(FRAMEDATA *fData){
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
					copy(fData);
					printf("\nCopy successful\n");
					clipExit = 1;
					pause();
					break;
			case 60: // return to paint funtion
				printf("\nCopy cancelled\n");
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
			(*fData).clipStringPTR[k] = (*fData).frameStringBUPTR[blockID];
			k++;
		}
	}
}

void clipDown(FRAMEDATA *fData){
	int i, ch;
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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
		//paste();
		// +++++++++++++++++++++++++++++++++++++++++++++++ YOU WERE ABOUT TO FINISH THE paste() FUNCTION NEXT
		
		printf("%s%s\nF1- | F2-", cls, (*fData).frameStringPTR);
		
		//selection
		ch = getch();
		if(ch == 224){
			switch(getch()){
			case 72:
				if(clipPosRow < 1 - (*fData).clipRows){
					continue;
				}
				clipPosRow--;
				break;
			case 75:
				if(clipPosCol < 1 - (*fData).clipCols){
					continue;
				}
				clipPosCol--;
				break;
			case 80:
				if((*fData).rows < clipPosRow){
					continue;
				}
				clipPosRow++;
				break;
			case 77:
				if((*fData).cols < clipPosCol){
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
					pause();
					continue;
			case 60:
				// exit
				
				pause();
				continue;
			case 61:
				// add a "preview original framestring" function here
				
				pause();
				continue;
			}
		}	
	}
}

void paste(FRAMEDATA *fData){
	
	
	/*
	gives the top left block of the copied blocks position(row, coluwm) that is relative to the (0, 0) position.
	these coordinates may be negative, but at least one block in the block must have a valid position within the canvas at all times.
	NOTE that positions of all blocks aren't generated. Instead the valid range of positions of the top left block is calculated.
	*/
}
//select function -- done, clip()

//copy function -- done, copy()

//paste function -- in progress

//undo+redo paste function

// "good selection" checker to stop users for doing bad crops

/*
the clipboard consists of 2 memory blocks
1) contains the copied block
2) contains th data in the block that the paste function
	pasted onto. To be used by the undo unction.
*/
