#ifndef __TASK2__
#define __TASK2__

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hasMemoryAllocationError(const char *buffer);
char *getLine(FILE *filePointer);
void strReverse(char *str);
void test_task2(char *argv[]);

#endif

