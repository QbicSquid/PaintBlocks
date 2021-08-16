#ifndef PAINTB_H
#define PAINTB_H
#include <iostream>

class canvas {
	protected:
		typedef struct FS{
			unsigned char *frameString;
			struct FS *next;
			struct FS *prev;
			int index;
		} FS;
		
		FS *head;
		int rows;
		int cols;
		int cursorRow;
		int cursorCol;
		unsigned char cursorMem;
//		int count; add this to "animation" child class

	private:
		void cursorAdd();

	public:	
		canvas(int rows, int cols);
		void setBlock(int row, int col, int key);
		

		print() { // debug
			std::cout << head->frameString;
		}
};

#endif

