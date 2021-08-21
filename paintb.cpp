#include <iostream>
#include "paintb.h"
using namespace std;


// canvas:
canvas::canvas(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;

	head = new FS;
	head->frameString = new unsigned char[(rows + 2) * (cols + 3)];
	head->next = NULL;
	head->prev = NULL;
	head->index = 0;

	// initialize framestring
	head->frameString[0] = 218;
	for(int c = 1; c < cols + 1; c++) {
		head->frameString[c] = 196;
	}
	head->frameString[cols + 1] = 191;
	head->frameString[cols + 2] = '\n';

	for(int r = 1; r < rows + 1; r++) {
		head->frameString[r * (cols + 3)] = 179;
		
		for(int c = 1; c < cols + 1; c++) {
			head->frameString[c + r * (cols + 3)] = ' ';
		}
		
		head->frameString[(r + 1) * (cols + 3) - 2] = 179;
		head->frameString[(r + 1) * (cols + 3) - 1] = '\n';
	}

	head->frameString[(cols + 3) * (rows + 1)] = 192;
	for(int c = 1; c < cols + 1; c++) {
		head->frameString[(cols + 3) * (rows + 1) + c] = 196;
	}
	head->frameString[(cols + 3) * (rows + 2) - 2] = 217;
	head->frameString[(cols + 3) * (rows + 2) - 1] = '\0';
	// framestring initialized
}

void canvas::setBlock(int row, int col, int key) {
	if(0 <= key && key < 256){
		head->frameString[col + row * (cols + 3)] = key;
	}
}

// cursor:
canvasCRS::canvasCRS(int rows, int cols) : canvas(rows, cols) {
	cursorRow = 0;
	cursorCol = 0;
	cursorMem = 206;
}

void canvasCRS::cursorToggle() {
	FS *current = head;
	unsigned char temp;
	int rawPos;

	while(current->next != NULL){
		current = current->next;
	} // getting to current frame on multi frame scenarios
	// might break when adding animations. CARE

	rawPos = cursorCol + 1 + (cursorRow + 1) * (cols + 3);

	temp = current->frameString[rawPos];
	current->frameString[rawPos] = cursorMem;
	cursorMem = temp;
}

