#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	canvasCRS cnv(10, 20);
	cnv.toggleCursor();
	cnv.toggleFocusedMode();
	
	cnv.saveCanvas("savefile");// debug line

	char key;
	while (true) {
		cnv.print();
		key = getch();
		cnv.cursorMov(key);
	}

	return 0;
}

