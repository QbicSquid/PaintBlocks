#ifndef PAINTB_H_   /* Include guard */
#define PAINTB_H_

#ifndef COMPKEY
#define COMPKEY 1548
#endif

typedef struct FRAMEDATA{
	unsigned char *frameStringPTR;
	int rows;
	int cols;
	int cursorRow;
	int cursorCol;
	unsigned char cursorMem;
	
	unsigned char *frameStringBUPTR;
	unsigned char *clipStringPTR;
	unsigned char *undoStringPTR;
	int clipRows;
	int clipCols;
}FRAMEDATA;

//paintb.c
void initNewCanvas(FRAMEDATA *fData);
void blockEdit(FRAMEDATA *fData, int blockRow, int blockCol, int key);
void cursorMove(FRAMEDATA *fData, int key);
void cursorAdd(FRAMEDATA *fData);
void cursorRem(FRAMEDATA *fData);
void cursorRestore(FRAMEDATA *fData);
void pause();
int loadFile(FRAMEDATA *fData, char fileName[]);
int saveFile(FRAMEDATA *fData, char fileName[]);

//image_edit.c
void paint(FRAMEDATA *fData);
void clipBlockEdit(FRAMEDATA *fData, int blockRow, int blockCol, int key);
void clipUp(FRAMEDATA *fData);
void copy(FRAMEDATA *fData);
int clipDown(FRAMEDATA *fData); // returns 1 if the paste was done. Returns 0 otherwise
void paste(FRAMEDATA *fData, int clipPosRow, int clipPosCol);
void undo(FRAMEDATA *fData);

#endif
