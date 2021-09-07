#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	unsigned char key;
	unsigned char value;
	canvasCRS cnv(20, 60);
	cnv.setFocusedMode(true);
	cnv.setMouseInput(true);

	cnv.maximize();
	cnv.focusedBGInputLoop('c');
	cnv.setCursorStatus(true);

	while (true) {
		cnv.print();
		key = getch();

		if(key == 'm' || key == 'M') {
			cnv.setCursorStatus(false);
			cnv.print();
			cnv.focusedBGInputLoop('c');
			cnv.setCursorStatus(true);
			continue;
		}

		if(key == 224) {
			key = getch();
			switch(key) {
				case 72: cnv.cursorMov(cnv.getCRow() - 1, cnv.getCCol()); break;
				case 75: cnv.cursorMov(cnv.getCRow(), cnv.getCCol() - 1); break;
				case 80: cnv.cursorMov(cnv.getCRow() + 1, cnv.getCCol()); break;
				case 77: cnv.cursorMov(cnv.getCRow(), cnv.getCCol() + 1); break;
			}
		}
		else if(65 <= key && key <= 90) {
			value = ' ';
		}
		else if(97 <= key && key <= 122){
			value = 219;
		}
		else {
			continue;
		}

		if(key == 'w' || key == 'W') {
		cnv.setBlock(cnv.getCRow() - 1, cnv.getCCol(), value);
		}
		else if(key == 'a' || key == 'A') {
			cnv.setBlock(cnv.getCRow(), cnv.getCCol() - 1, value);
		}
		else if(key == 's' || key == 'S') {
			cnv.setBlock(cnv.getCRow() + 1, cnv.getCCol(), value);
		}
		else if(key == 'd' || key == 'D') {
			cnv.setBlock(cnv.getCRow(), cnv.getCCol() + 1, value);
		}
	}

	return 0;
}

