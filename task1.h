#ifndef __TASK1__
#define __TASK1__

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBytes(void *ptr, int numBytes);
int isFileOpenError(FILE *writeFilePointer, char fileName[]);
void test_task1();

#endif

