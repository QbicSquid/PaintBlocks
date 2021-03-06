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

canvas::~canvas() {
	delete head->frameString;
	delete head;
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
	focusedMode = false;
	mouseInput = false;
	block = 219;
	display = NULL;
	displayColor = NULL;
	
	// initializing color support
	color = 7;
	colorHead = new FS;
	colorHead->frameString = new unsigned char[(rows + 2) * (cols + 3)];
	colorHead->next = NULL;
	colorHead->prev = NULL;
	
	for(int i =0; i < (rows + 2) * (cols + 3); i++) {
		colorHead->frameString[i] = 7;
	}
	// color support initialized

	// initializing console manipulation
	cohan = GetStdHandle(STD_OUTPUT_HANDLE);
	cihan = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(cihan, &consoleMode_prev);

	cfi_prev.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(cohan, FALSE, &cfi_prev); // to restore later
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.dwFontSize.X = 4;
	cfi.dwFontSize.Y = 6;
	wcscpy(cfi.FaceName, L"Terminal");
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	cfi.nFont = 0;


	topLeft.X = 0;
	topLeft.Y = 0;

	cci.dwSize = 25;
	cci.bVisible = FALSE;
	// console manipulation initialized
}

canvasCRS::~canvasCRS() {
	SetConsoleMode(cihan , consoleMode_prev); // restoring previous consome mode
	SetCurrentConsoleFontEx(cohan, FALSE, &cfi_prev);
	cls();
	
	delete colorHead->frameString;
	delete colorHead;
	if(display != NULL) {
		delete display;
	}
}

void canvasCRS::cls()  {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(cohan, &csbi)) {
		// handle failure
		return;
	}

	DWORD written = 0;
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(cohan, TEXT(' '),
		length, topLeft, &written); // fill the console with spaces
	FillConsoleOutputAttribute(cohan, csbi.wAttributes,
		length, topLeft, &written); // clear background color formatting, if any

	SetConsoleCursorPosition(cohan, topLeft);
	//reset console cursor
}

void canvasCRS::print() {
	if(focusedMode == false) {
		print_fs();
		// TODO: add a proper unfocused print functionality here
		return;
	}

	SetConsoleCursorInfo(cohan, &cci);
	// in case the console resized, making the console cursor invisible

	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		if(display[i] == head->frameString[i] && 
			displayColor[i] == colorHead->frameString[i]) {
			continue;
		}

		display[i] = head->frameString[i];
		displayColor[i] = colorHead->frameString[i];
		jumpTo.X = i % (cols + 3);
		jumpTo.Y = i / (cols + 3);

		SetConsoleCursorPosition(cohan, jumpTo);
		SetConsoleTextAttribute(cohan, displayColor[i]);
		
		WriteConsole(cohan, &display[i],
		1, NULL, NULL); // print
		
	}
}

void canvasCRS::printFull(){
	std::cout.flush();
	cls();
	SetConsoleCursorPosition(cohan, topLeft);
	// reset the console cursor
	SetConsoleCursorInfo(cohan, &cci);
	// in case the console resized, making the console cursor invisible
	
	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		SetConsoleTextAttribute(cohan, displayColor[i]);
		
		WriteConsole(cohan, &display[i],
		1, NULL, NULL); // print
	}
	SetConsoleTextAttribute(cohan, 7);
}

void canvasCRS::refreshDisplayString() {
	displayColor = new unsigned char[(rows + 2) * (cols + 3)];
	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		displayColor[i] = colorHead->frameString[i];
	}
	
	display = new unsigned char[(rows + 2) * (cols + 3)];
	for(int i = 0;i < (rows + 2) * (cols + 3); i++) {
		display[i] = head->frameString[i];
	}
}

void canvasCRS::maximize() {
	HWND thisWH = GetForegroundWindow();
	ShowWindow(thisWH, SW_MAXIMIZE);
	Sleep(100);
}

void canvasCRS::setFocusedMode(bool state) {
	if(focusedMode == state) {return; }

	if(focusedMode == true){
		delete display;
		SetCurrentConsoleFontEx(cohan, FALSE, &cfi_prev); // restoring font
		focusedMode = false;
		return;
	}

	refreshDisplayString(); // initializing display and displayColor FS

	SetCurrentConsoleFontEx(cohan, FALSE, &cfi); // setting font

	// saving the position to move the cursor back to
	jumpBack.X = 0;
	jumpBack.Y = rows + 2;

	focusedMode = true;
}

void canvasCRS::setMouseInput(bool state) {
	if(mouseInput == state) { return; }
	if(state == false) {
		SetConsoleMode(cihan , consoleMode_prev);
		SetCurrentConsoleFontEx(cohan, FALSE, &cfi_prev);
		state = false;
		return;
	}

	mouseInput = true;
	SetConsoleMode(cihan ,ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
}

unsigned char canvasCRS::inputLoop() {
	if(focusedMode == false) { return 0; }
	
	INPUT_RECORD inputRecord;
	DWORD numOfEventsRead;
	unsigned char out;
	unsigned char outColor;

	while(true) {
		ReadConsoleInput(cihan, &inputRecord, 1, &numOfEventsRead);

		switch(inputRecord.EventType) {
			case WINDOW_BUFFER_SIZE_EVENT:
				SetConsoleCursorPosition(cohan, topLeft);
				cls();
				WriteConsole(cohan, head->frameString,
					(rows + 2) * (cols + 3), NULL, NULL); // print
				WriteConsole(cohan, "\n", 1, NULL, NULL); // newline
				continue;

			case MOUSE_EVENT:
				if(mouseInput == false) { continue; }
				break;

			case KEY_EVENT:
				if(inputRecord.Event.KeyEvent.bKeyDown) {
					SetConsoleCursorPosition(cohan, jumpBack);
					// moveing the console cursor to jumpBack position
					SetConsoleTextAttribute(cohan, 7);
					// resetting output color
					return inputRecord.Event.KeyEvent.uChar.AsciiChar;
				}

			default:
				continue;
		}

		switch(inputRecord.Event.MouseEvent.dwButtonState){
			case FROM_LEFT_1ST_BUTTON_PRESSED:
				out = block;
				outColor = color;
				break;
			case RIGHTMOST_BUTTON_PRESSED:
				out = ' ';
				outColor = 7;
				break;
			default:
				continue;
		}

		int Y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
		int X = inputRecord.Event.MouseEvent.dwMousePosition.X;

		if(Y == 0 || Y >= rows + 1 || X == 0 || X >= cols + 1) { continue; }

		// TODO: make a paint(int size) function and call it here
		head->frameString[rawPos(Y - 1, X - 1)] = out;
		colorHead->frameString[rawPos(Y - 1, X - 1)] = outColor;
		
		print();

		redrawConsole();
	}
}

void canvasCRS::changeColor(int newColor) {
	if(newColor == -1) { color = 7; }
	
	if(0 < newColor && newColor < 16) {
		color = newColor;
	}
}

void canvasCRS::zoomIn() {
	switch(cfi.dwFontSize.X){
		case 4:
			cfi.dwFontSize.X = 8;
			cfi.dwFontSize.Y = 12;
			break;
		case 8:
			cfi.dwFontSize.X = 12;
			cfi.dwFontSize.Y = 16;
			break;
		default:
			return;
	}

	SetCurrentConsoleFontEx(cohan, FALSE, &cfi);
}

void canvasCRS::zoomOut() {
	switch(cfi.dwFontSize.X){
		case 8:
			cfi.dwFontSize.X = 4;
			cfi.dwFontSize.Y = 6;
			break;
		case 12:
			cfi.dwFontSize.X = 8;
			cfi.dwFontSize.Y = 12;
			break;
		default:
			return;
	}

	SetCurrentConsoleFontEx(cohan, FALSE, &cfi);
}

int canvasCRS::loadCanvas(std::string fileName) {
	std::ifstream file(fileName.data());
	if(!file) {return -1; }

	int compKey = 0;
	file >> compKey;
	if(compKey != COMP_KEY) {return -2; }

	file >> rows >> cols;
	
	// creating new framestring and colorstring
	delete head->frameString;
	delete colorHead->frameString;
	
	head->frameString = new unsigned char[(rows + 2) * (cols + 3)];
	colorHead->frameString = new unsigned char[(rows + 2) * (cols + 3)];
	
		// initializing frameStringColor
	for(int i =0; i < (rows + 2) * (cols + 3); i++) {
		colorHead->frameString[i] = 7;
	}
		// frameStringColor initialized!
	
		// initializing framestring border
	head->frameString[0] = 218;
	for(int c = 1; c < cols + 1; c++) {
		head->frameString[c] = 196;
	}
	head->frameString[cols + 1] = 191;
	head->frameString[cols + 2] = '\n';

	for(int r = 1; r < rows + 1; r++) {
		head->frameString[r * (cols + 3)] = 179;
		
		head->frameString[(r + 1) * (cols + 3) - 2] = 179;
		head->frameString[(r + 1) * (cols + 3) - 1] = '\n';
	}

	head->frameString[(cols + 3) * (rows + 1)] = 192;
	for(int c = 1; c < cols + 1; c++) {
		head->frameString[(cols + 3) * (rows + 1) + c] = 196;
	}
	head->frameString[(cols + 3) * (rows + 2) - 2] = 217;

	head->frameString[(cols + 3) * (rows + 2) - 1] = '\0';
		// framestring border initialized!
	// framsetring and colorstring craetion done!
	
	file.ignore(1);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			head->frameString[rawPos(i, j)] = (unsigned char)file.get();
		}
	}

	file.ignore(1);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			colorHead->frameString[rawPos(i, j)] = (unsigned char)file.get();
		}
	}
	
	// reloading display string
	if(display != NULL){
		delete display;
		display = new unsigned char[(rows + 2) * (cols + 3)];
		
		delete displayColor;
		displayColor = new unsigned char[(rows + 2) * (cols + 3)];
		
		refreshDisplayString(); // refresh displayString and displaColorString
	}
	// reloading display string done!

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

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			file << head->frameString[rawPos(i, j)];
		}
	}

	file << "\n";

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			file << colorHead->frameString[rawPos(i, j)];
		}
	}

	file.close();
	return 0;
}

void canvasCRS::redrawConsole() { // redraw console window
	HWND winHandle = GetForegroundWindow(); // get window handle
	InvalidateRect(winHandle, NULL, FALSE); // queue window for updating
	UpdateWindow(winHandle); // update window
}

