#include <stdio.h>
#include "paintb.h"


int main(){
	unsigned char frameString[8500];
	unsigned char frameStringBU[8500];
	unsigned char clipString[8500];
	unsigned char undoString[8500];
	
	FRAMEDATA fData;
	fData.frameStringPTR = frameString;
	fData.frameStringBUPTR = frameStringBU;
	fData.clipStringPTR = clipString;
	fData.undoStringPTR = undoString;
	fData.clipRows = -99;
	
	char fileName[255];
	char cls[65] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	int ch;
	
	while(1){
		printf("%s___Paint Blocks(v0.4.2 beta)___\n\n\n1) New\n2) Load\n3) Help\n\n>> ", cls);
		ch = getch();
		printf("%c\n\n", ch);
		if(ch == '1'){
			while(1){
				printf("\n\nEnter Canvas Dimentions: \nrows(0<   <=50):\n");
				scanf("%d", &fData.rows);
				if(fData.rows < 1 || fData.rows > 50){
					continue;
				}
				printf("\nColumns(0<   <=160:)\n");
				scanf("%d", &fData.cols);
				if(fData.cols < 1 || fData.cols > 160){
					continue;
				}
				
				initNewCanvas(&fData);
				break;
			}
		}
		else if(ch == '2'){
			printf("\n\n\nEnter File Name:\n");
			printf("(File must be in the same directory as the program and must have no spaces)\n");
			printf("Enter 'q' to cancel\n");
			scanf("%s", fileName);
			
			if(fileName[0] == 'q' && fileName[1] == '\0'){
				printf("Load cancelled\n");
				pause();
				continue;
			}
			
			ch = loadFile(&fData, fileName); // loading framestring
			if(ch < 0){ // if framestring was not loaded properly
				return -1;
			}
			
			fData.rows = ch % 100;
			fData.cols = (ch - fData.rows) / 100;
			printf("checking -> %d %d\n", fData.rows, fData.cols);//debugging line
			cursorAdd(&fData);
		}
		else if(ch == '3'){
			char help1[] = "Help\n\n"
				"> Use arrow keys to move cursor.\n"
				"> Use WASD to place paint blocks.\n"
				"> Use Shift/CapsLock + WASD to erase paint blocks.\n"
				"> Use F keys to access additional functionality.(Copy/Pase/Undo/Redo).\n\n";
			char help2[] = "Using the copy/pase functionality.\n"
				"> Press the copy key(F5).\n"
				"> Select the exact blocks you wish to copy(using WASD and arrow keys).\n"
				"> Press F1 to copy.\n"
				"> You will now be at the initial canvas, press the paste key(F6) to paste.\n"
				"> Navigate using the arrow keys and press F1 to confirm the paste.\n\n";
			char help3[] = "Using the undo/redo functionality\n"
				"> Press F7 while in the canvas to undo or redo the previous paste.\n"
				"> The functionaly will be lost when you paint/erase a paint block.\n"
				"> It will be usable again afte the next paste.\n"
				"> Moving the cursor does not affect the availability of the undo/redo function.\n\n";
			printf("%s", cls);
			printf("%s", help1);
			pause();
			printf("\n\n%s", help2);
			pause();
			printf("\n\n%s", help3);
			pause();
			continue;
		}
		else{
			continue;
		}
	
	paint(&fData);
	}
	
	return 0;
}
