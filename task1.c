#include "task1.h"

/**
 * This function checks for errors after a file has been opened, & exits the program if an error is found.
 *
 * @param writeFilePointer the pointer to the opened file
 * @param fileName the name of the file that has been opened e.g. file.txt
 * @return 1 if no errors have occurred\n\n
 *         if an error occurs: outputs an error message to stdout & stderr then exits the program with code 1
 */
int isFileOpenError(FILE *writeFilePointer, char fileName[]) {
    if (writeFilePointer == NULL) {
        printf("the file: '%s' cannot be opened with write access.", fileName);
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        exit(1);
    }

    return 1;   /* no errors */
}


/**
 *  This function prints out the decimal values stored in the numBytes contiguous memory locations starting at the
 *  memory address pointed to by ptr.\n
 *    
 *  @param ptr a pointer that points to the memory location to start printing bytes from
 *  @param numBytes the number of bytes to print
 *       
 *   \Example_Output
 *   Starting at memory address XXXXXX:\n
 *   001:  10\n
 *   002:  20\n
 *   003:  30\n
 *   004: 145\n
 */
void printBytes(void *ptr, int numBytes) {
    int i;

    printf("Starting at memory address %p:\n", ptr);
    for (i = 1; i <= numBytes; i++) {
        printf("%03d: %3d\n", i, *(unsigned char *) ptr);   /* Output byte number & value to terminal */
        ptr++;
    }

}


/**
 * This functions contains tests for Task1 of the CA. It runs multiple test conditions & outputs the results to the
 * terminal
 */
void test_task1() {
    printf("\n--TASK 1--\n");
    unsigned char arr[4] = {'a', 'b', 'c', 'd'};
    printBytes(arr, sizeof(unsigned char) * 4);
    printf("\n");

    char *task1String = "Hello World!";
    printBytes(task1String, sizeof(char) * 12);
    printf("\n");

    unsigned int unsignedIntArr[4] = {1, 2, 3, 4};
    printBytes(unsignedIntArr, sizeof(unsigned int) * 4);
    printf("\n");

    int intArr[2] = {-1, INT_MIN};
    printBytes(intArr, sizeof(int) * 2);
    printf("\n");
}
