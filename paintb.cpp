#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "paintb.h"

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

int canvas::rawPos(int row, int col) {
	return (col + 1) + (row + 1) * (cols + 3);
}

int canvas::logRow(int rawPos) {
	int row = rawPos / (cols + 3);
	if(row == 0 || row + 1 == rows) {return -1;}
	return row - 1;
}

int canvas::logCol(int rawPos) {
	int col = rawPos % (cols + 3);
	if(col == 0 || col > cols) {return -1;}
	return col - 1;
}

void canvas::setBlock(int row, int col, int key) {
	if(row < 0 || row >= rows || col < 0 || col >= cols) {return; }

	if(0 <= key && key < 256){
		head->frameString[rawPos(row, col)] = key;
	}
}

void canvas::print_fs() {
	std::cout << head->frameString << std::endl;
}

// cursor:
canvasCRS::canvasCRS(int rows, int cols) : canvas(rows, cols) {
	cursorRow = 0;
	cursorCol = 0;
	cursorMem = 233;
	cursor = false;
	focusedMode = false;

	// initializing console manipulation
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	topLeft.X = 0;
	topLeft.Y = 0;
	
	info.dwSize = 25;
	info.bVisible = FALSE;
	// console manipulation initialized
}

void canvasCRS::setCursor(bool state) {
	if(cursor == state) {return; }

	cursor = state;

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

void canvasCRS::cursorMov(int key) {
	if(cursor == false) {return; }

	setCursor(false);

	switch (key) {
		case 'w':
			if (0 < cursorRow) { --cursorRow; }
			break;
		case 'a':
			if (0 < cursorCol) {--cursorCol; }
			break;
		case 's':
			if (cursorRow < rows - 1) { ++cursorRow; }
			break;
		case 'd':
			if (cursorCol < cols - 1) { ++cursorCol; }
			break;
	}

	setCursor(true);
}

void canvasCRS::print() {
	if(focusedMode == false) {
		print_fs();
		return;
	}

	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		if(display[i] == head->frameString[i]) {
			continue;
		}

		display[i] = head->frameString[i];
		jumpTo.X = i % (cols + 3) - 1;
		jumpTo.Y = i / (cols + 3);
		out[0] = display[i - 1];
		out[1] = display[i];

		SetConsoleCursorInfo(consoleHandle, &info);
		// in case the console resized, making the console cursor invisible

		SetConsoleCursorPosition(consoleHandle, jumpTo);
		WriteConsole(consoleHandle, out,
		2, NULL, NULL); // print

		SetConsoleCursorPosition(consoleHandle, jumpBack);
		// moveing the console cursor to jumpBack position
	}
}

void canvasCRS::setFocusedMode(bool state) {
	if(focusedMode == state) {return; }

	if(focusedMode == true){
		delete display;
		focusedMode = false;
		return;
	}
	
	display = new unsigned char[(rows + 2) * (cols + 3)];
	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		display[i] = head->frameString[i];
	}

	std::cout.flush();
	cls();
	SetConsoleCursorPosition(consoleHandle, topLeft);
	// reset the console cursor
	SetConsoleCursorInfo(consoleHandle, &info);
	// in case the console resized, making the console cursor invisible

	WriteConsole(consoleHandle, head->frameString,
		(rows + 2) * (cols + 3), NULL, NULL); // print
	WriteConsole(consoleHandle, "\n", 1, NULL, NULL); // newline

	// saving the position to move the cursor back to
	jumpBack.X = 0;
	jumpBack.Y = rows + 2;

	focusedMode = true;
}

void canvasCRS::cls()  {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(consoleHandle, &csbi)) {
		// handle failure
		return;
	}

	DWORD written = 0;
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(consoleHandle, TEXT(' '),
		length, topLeft, &written); // fill the console with spaces
	FillConsoleOutputAttribute(consoleHandle, csbi.wAttributes,
		length, topLeft, &written); // clear background color formatting, if any

	SetConsoleCursorPosition(consoleHandle, topLeft);
	//reset console cursor
}

int canvasCRS::getCRow() {
	return cursorRow;
}

int canvasCRS::getCCol() {
	return cursorCol;
}

int canvasCRS::loadCanvas(std::string fileName) {
	std::ifstream file(fileName.data());
	if(!file) {return -1; }

	int compKey = 0;
	file >> compKey;
	if(compKey != COMP_KEY) {return -2; }

	file >> rows >> cols;
	file.ignore(1);
	setCursor(false);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			head->frameString[rawPos(i, j)] = file.get();
		}
	}
	setCursor(true);

	file.close();
	return 0;
}

int canvasCRS::saveCanvas(std::string fileName) {
	std::ifstream checkIfOpen(fileName.data());
	if(checkIfOpen) {return -1;} // checking whther the file already exists
	checkIfOpen.close();

	(void)saveCanvasForce(fileName);

	return 0;
}

int canvasCRS::saveCanvasForce(std::string fileName) {
	std::ofstream file(fileName.data());

	if(!file) {return -1; }

	file << COMP_KEY << "\n" << rows << " " << cols << "\n";

	setCursor(false);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			file << head->frameString[rawPos(i, j)];
		}
	}
	setCursor(true);

	file.close();
	return 0;
}

