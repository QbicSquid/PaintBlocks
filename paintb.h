#ifndef PAINTB_H
#define PAINTB_H
#include <iostream>

class canvas {
	protected:
		typedef struct FS {
			unsigned char *frameString;
			struct FS *next;
			struct FS *prev;
			int index;
		} FS;

		FS *head;
		int rows;
		int cols;
//		int count;
//		Made for compatibility with multi frame objects.
//		Move to "animation" class.

	public:	
		canvas(int rows, int cols);
		void setBlock(int row, int col, int key);


		void print(); // debug
};

class canvasCRS: public canvas {
	private:
		int cursorRow;
		int cursorCol;
		unsigned char cursorMem;

	public:
		canvasCRS(int rows, int cols);
		void cursorToggle();
		void cursorMov(int key);
}; 

#endif

