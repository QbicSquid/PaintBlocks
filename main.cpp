#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	canvasCRS cnv(10, 20);
	cnv.setCursor(true);
	cnv.setFocusedMode(true);

	int key;
	while (true) {
		cnv.print();
		key = getch();

		if(key == 224) {
			switch(getch()) {
				case 72:
					cnv.setBlock(cnv.getCRow() - 1, cnv.getCCol(), 219);
					break;
				case 75:
					cnv.setBlock(cnv.getCRow(), cnv.getCCol() - 1, 219);
					break;
				case 80:
					cnv.setBlock(cnv.getCRow() + 1, cnv.getCCol(), 219);
					break;
				case 77:
					cnv.setBlock(cnv.getCRow(), cnv.getCCol() + 1, 219);
					break;
			}
		}
		else if(key == 107) {
			cnv.saveCanvas("save1");
		}
		else {
			cnv.cursorMov(key);
		}
	}

	return 0;
}

