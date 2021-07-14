#include <stdio.h>
#include "paintb.h"


void initNewCanvas(FRAMEDATA *fData){
	int i = 0, j;
	// initializing the frame string
	(*fData).frameStringPTR[0] = 218;
	for(i = 1; i < (*fData).cols + 1; i++){
		(*fData).frameStringPTR[i] = 196;
	}
	(*fData).frameStringPTR[(*fData).cols + 1] = 191;
	(*fData).frameStringPTR[(*fData).cols + 2] = '\n';
	
	for(i = 1; i < (*fData).rows + 1; i++){
		(*fData).frameStringPTR[i * ((*fData).cols + 3)] = 179;
		for(j = 1; j < (*fData).cols + 1; j++){
			(*fData).frameStringPTR[i * ((*fData).cols + 3) + j] = ' ';
		}
		(*fData).frameStringPTR[i * ((*fData).cols + 3) + ((*fData).cols + 1)] = 179;
		(*fData).frameStringPTR[i * ((*fData).cols + 3) + ((*fData).cols + 2)] = '\n';
	}
	
	(*fData).frameStringPTR[((*fData).rows + 1) * ((*fData).cols + 3)] = 192;
	for(i = 1; i < (*fData).cols + 1; i++){
		(*fData).frameStringPTR[((*fData).rows + 1) * ((*fData).cols + 3) + i] = 196;
	}
	(*fData).frameStringPTR[((*fData).rows + 1) * ((*fData).cols + 3) + ((*fData).cols + 1)] = 217;
	(*fData).frameStringPTR[((*fData).rows + 1) * ((*fData).cols + 3) + ((*fData).cols + 2)] = '\0';
	
	// adding the cursor
	cursorAdd(fData);
	// initializing complete
}

void blockEdit(FRAMEDATA *fData, int blockRow, int blockCol, int key){
	int blockID;
	blockID = (blockRow + 1) * ((*fData).cols + 3) + (blockCol + 1);
	
	switch(key){
		case 0: (*fData).frameStringPTR[blockID] = ' '; break;
		case 1: (*fData).frameStringPTR[blockID] = 219; break;
		case 2: (*fData).frameStringPTR[blockID] = 206; break;
	}
}

void cursorMove(FRAMEDATA *fData, int key){
	int currentBlockID, nextBlockID;
	char nextBlockVal;
	
	currentBlockID = ((*fData).cursorRow + 1) * ((*fData).cols + 3) + ((*fData).cursorCol + 1);
	switch(key){
	case 1:
		(*fData).cursorRow--;
		nextBlockID = currentBlockID - ((*fData).cols + 3);
		break;
	case 2:
		(*fData).cursorCol--;
		nextBlockID = currentBlockID - 1;
		break;
	case 3:
		(*fData).cursorRow++;
		nextBlockID = currentBlockID + ((*fData).cols + 3);
		break;
	case 4:
		(*fData).cursorCol++;
		nextBlockID = currentBlockID + 1;
		break;
	}
	
	(*fData).frameStringPTR[currentBlockID] = (char)(*fData).cursorMem;
	(*fData).cursorMem = (char)(*fData).frameStringPTR[nextBlockID];
	(*fData).frameStringPTR[nextBlockID] = 206;
	/*
	1) Restore the value that was in the cursor's current position
	2) Store the cursor's next position's value in cursorData
	3) Put the cursor in the next position
 	*/
}

void cursorAdd(FRAMEDATA *fData){
	(*fData).cursorRow = 0;
	(*fData).cursorCol = 0;
	(*fData).cursorMem = (*fData).frameStringPTR[(*fData).cols + 4];
	(*fData).frameStringPTR[(*fData).cols + 4] = 206;
}

void cursorRem(FRAMEDATA *fData){
	(*fData).frameStringPTR[((*fData).cursorRow + 1) * ((*fData).cols + 3) + ((*fData).cursorCol + 1)] = (*fData).cursorMem;
}

void cursorRestore(FRAMEDATA *fData){
	(*fData).cursorMem = (*fData).frameStringPTR[((*fData).cursorRow + 1) * ((*fData).cols + 3) + ((*fData).cursorCol + 1)];
	(*fData).frameStringPTR[((*fData).cursorRow + 1) * ((*fData).cols + 3) + ((*fData).cursorCol + 1)] = 206;
}

void pause(){
	unsigned char ch;
	puts("Press any key to continue");
	ch = getch();
	if(ch == 0 || ch == 224){
		ch == getch();
	}
}

int loadFile(FRAMEDATA *fData, char fileName[]){
	int compKey, rows, cols, i;
	
	FILE *dataFile;
	dataFile = fopen(fileName, "r");
	if(dataFile == NULL){
		return -1;
	}
	
	fscanf(dataFile, "%d\n", &compKey);
	if(compKey != COMPKEY){
		return -2;
	}
	fscanf(dataFile , "%d,", &(*fData).rows);
	fscanf(dataFile , "%d\n", &(*fData).cols);
	printf("checking -> %d %d\n", (*fData).rows, (*fData).cols);//debugging line
	for(i = 0; i < ((*fData).cols + 3) * ((*fData).rows + 2); i++){
		fscanf(dataFile, "%u,", &(*fData).frameStringPTR[i]);
	}
	fclose(dataFile);
	return ((*fData).cols * 100) + (*fData).rows;
}

int saveFile(FRAMEDATA *fData, char fileName[]){
	int i;
	
	FILE *dataFile;
	dataFile = fopen(fileName, "r");
	if(dataFile != NULL){
		return -1;
	}
	fclose(dataFile);
	dataFile = fopen(fileName, "w");
	
	fprintf(dataFile, "1548\n%d,%d\n", (*fData).rows, (*fData).cols);
	for(i = 0; i < ((*fData).cols + 3) * ((*fData).rows + 2); i++){
		fprintf(dataFile, "%u,", (*fData).frameStringPTR[i]);
	}
	
	fclose(dataFile);
	return 0;
}
