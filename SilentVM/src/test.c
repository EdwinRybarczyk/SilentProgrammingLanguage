#include <stdlib.h>
#include <stdio.h> 
#include "SilentVM.h"

int main()
{
	int p = 0;
	char* b = malloc(500);
	b[p++] = Push4;
	b[p++] = 51;
	b[p++] = 51;
	b[p++] = -109;
	b[p++] = 64;
	b[p++] = Push4;
	b[p++] = 0;
	b[p++] = 0;
	b[p++] = -112;
	b[p++] = 64;
//	b[p++] = Push4;
//	b[p++] = 254;
//	b[p++] = 0;
//	b[p++] = 0;
//	b[p++] = 0;
//	b[p++] = Push4;
//	b[p++] = 2;
//	b[p++] = 0;
//	b[p++] = 0;
//	b[p++] = 0;
	b[p++] = DivFloat;
	b[p++] = Halt;

	SilentMemory* m = createSilentMemory(500,500);
	SilentThread* t = createSilentThread(m, b);

	executeSilentThread(t);
	printf("%i\n",m->stackPointer);
	printf("%f\n", *(float*)(m->stack + 0));
return 0;
}