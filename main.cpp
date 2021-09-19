#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	int rows, cols;
	
	std::cout << "Enter the number of rows: " << "\n";
	std::cin >> rows;
	std::cout << "Enter the number of columnss: " << "\n";
	std::cin >> cols;
	
	canvasCRS cnv(rows, cols);
	cnv.setFocusedMode(true);
	cnv.setMouseInput(true);
	unsigned char key = 'r';

	cnv.maximize();
	cnv.printFull();
	
	while(key != 'q') {	
		switch(key) {
			case 'i':
				cnv.zoomIn();
				break;
			case 'o':
				cnv.zoomOut();
				break;
			case 'c':
				cnv.cls();
				cnv.zoomIn();
				cnv.zoomIn();
				std::cout << "HELLO! please wait for 1 second";
				Sleep(1000);
				cnv.printFull();
				break;
			case 's':
				cnv.saveCanvas("save1.pb");
				break;
			case 'l':
				cnv.loadCanvas("save1.pb");
				cnv.printFull();
				break;
			default:
				if('1' <= key && key <= '7') {
					cnv.changeColor(key - 48);
				}
				break;
		}
		
		key = cnv.inputLoop();
	}
}

