#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	unsigned char key;
	unsigned char value;
	bool cursor = true;
	canvasCRS cnv(30, 120);
	cnv.setCursor(true);
	cnv.setFocusedMode(true);

	// TODO: open another thread for the mouse;
	cnv.setMouseInput(true);
	cnv.focusedBGInputLoop();

	while (true) {
		cnv.print();
		key = getch();

		if(key == 't' || key == 'T') {
			if(cursor == true) {
				cursor = false;
				cnv.setCursor(false);
			}
			else {
				cursor = true;
				cnv.setCursor(true);
			}

			continue;
		}

		if(cursor == false) { continue; }

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

