#include "task2.h"

void test_task2(char *argv[]){
    /* open read file */
    FILE *readFilePointer;
    readFilePointer = fopen(argv[1], "r");
    isFileOpenError(readFilePointer, argv[1]);

    /* Read line 1 of the file into the buffer then close the file*/
    char *line = getLine(readFilePointer);
    strReverse(line);
    fclose(readFilePointer);

    /* open/create output file */
    FILE *writeFilePointer;
    writeFilePointer = fopen(argv[2], "w");
    isFileOpenError(writeFilePointer, argv[2]);

    /* Write to the output file then close the file*/
    fputs(line, writeFilePointer);
    fclose(writeFilePointer);

    /* Free dynamically assigned memory, prevents memory leaks */
    free(line);
}


/**
 *  checks if the buffer has been allocated memory correctly by checking whether it is set to NULL or not.
 *   
 *  @param buffer the buffer to check if memory has been correctly allocated to it
 *  @return 0 if memory has been allocated correctly.\n\n
 *          otherwise produces an error message via stdout & stderr then exits the program with exit code 1
 */
int hasMemoryAllocationError(const char *buffer) {
    if (buffer == NULL) {
        printf("Error caused when allocating memory to buffer.\n");
        fflush(stdin);
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        fflush(stderr);
        exit(1);
    }

    return 0;
}


/**
 *  dynamically assigns memory to a buffer & reads the first line of a file where the line is of an unknown length
 *   
 *  @param filePointer the file to read a line from
 *  @return the first line of the file
 */
char *getLine(FILE *filePointer) {
    int bufferSize = 64;                                    /* Allows for easy optimization of the program */
    char *buffer = malloc(bufferSize * sizeof(char));
    int index = 0;
    int ch;

    hasMemoryAllocationError(buffer);

    /* iterate through each letter in the file being read, and dynamically allocate  memory if the size of the buffer
     * is exceeded. */
    while ((ch = fgetc(filePointer)) != EOF && ch != '\n') {

        /* Resize the buffer if it's too small */
        if (index == bufferSize - 1) {
            bufferSize *= 2;
            buffer = realloc(buffer, bufferSize * sizeof(char));

            hasMemoryAllocationError(buffer);
        }

        buffer[index++] = ch;
    }
    buffer[index] = '\0';   /* Put a null pointer at the end of the string */
    return buffer;

}


/**
 * Reverses a string in-place
 *
 * @param str the string to reverse
 */
void strReverse(char *str) {
    int i, k;
    int length = strlen(str);
    char temp;

    for (i = 0, k = length - 1; i < k; i++, k--) {
        temp = str[i];
        str[i] = str[k];
        str[k] = temp;
    }
}
