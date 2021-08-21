#include <iostream>
#include "paintb.h"
using namespace std;


int main(void) {
	canvasCRS cnv(10, 20);
	cnv.print();

	int row, col, key;
	cin >> row >> col >> key;
	cnv.setBlock(row, col, key);
	cnv.print();
	
	cnv.cursorToggle();
	cnv.print();

	return 0;
}

