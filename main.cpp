#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	canvasCRS cnv(20, 80);
//	cnv.setCursor(true);
	cnv.setFocusedMode(true);
	
	// TODO: open another thread for the mouse;
	// TODO: on a resize event, redraw the whole canvas;
	cnv.setMouseInput(true);
	cnv.focusedMouseLoop();

//	unsigned char key;
//	while (true) {
//		cnv.print();
//		key = getch();
//
//		if(key == 224) {
//			switch(getch()) {
//				case 72: // arrow key up
//					cnv.setBlock(cnv.getCRow() - 1, cnv.getCCol(), 219);
//					break;
//				case 75: // arrow key left
//					cnv.setBlock(cnv.getCRow(), cnv.getCCol() - 1, 219);
//					break;
//				case 80: // arrow key down
//					cnv.setBlock(cnv.getCRow() + 1, cnv.getCCol(), 219);
//					break;
//				case 77: // arrow key right
//					cnv.setBlock(cnv.getCRow(), cnv.getCCol() + 1, 219);
//					break;
//			}
//		}
//		else {
//			switch(key) {
//				case 'k':
//				case 'K':
//					(void)cnv.saveCanvasForce("save1");
//					break;
//				case 'l':
//				case 'L':
//					(void)cnv.loadCanvas("save1");
//					break;
//				default:
//					(void)cnv.cursorMov(key);
//					break;
//			}
//		}
//	}

	return 0;
}

