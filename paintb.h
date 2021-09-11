#ifndef PAINTB_H
#define PAINTB_H
#define COMP_KEY 4826
#include <windows.h>
#include <string>

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

		int rawPos(int row, int col);
		int logRow(int rawPos);
		int logCol(int rawPos);

	public:	
		canvas(int rows, int cols);
		~canvas();
		void setBlock(int row, int col, int key);
		void print_fs(); // innefficient print function
};

class canvasCRS: public canvas {
	private:
		HANDLE cohan; // console output handle
		DWORD prevConsoleMode; // to restore in the destructor
		COORD topLeft;
		CONSOLE_CURSOR_INFO cci;
		// for console manipulation

		bool mouseInput;
		HANDLE cihan; // console input handle
		INPUT_RECORD inputRecord;
		unsigned char block;
		// for mouse input

		unsigned char *display;
		bool focusedMode;
		COORD jumpTo;
		COORD jumpBack;
		// for fast display refreshing (focused mode)

		void redrawConsole();

	public:
		canvasCRS(int rows, int cols);
		~canvasCRS();
		void setFocusedMode(bool state);
		void cls();
		void print();
		void maximize();
		void setMouseInput(bool state); // TODO: Finish mouse funnctions
		void inputLoop(unsigned char ExitKey);
		int loadCanvas(std::string fileName);
		int saveCanvas(std::string fileName);
		int saveCanvasForce(std::string fileName);
};

#endif

