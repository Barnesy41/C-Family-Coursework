#include "msString.h"
#include <errno.h>
#include <limits.h>

int msHasMemoryAllocationError(const void *buffer);

/**
 *  checks if the buffer for an msString has been allocated memory correctly by checking whether it is set to NULL or not.
 *  
 *  @param buffer the buffer to check if memory has been correctly allocated to it
 *  @return 0 if memory has been allocated correctly.\n\n
 *          otherwise calls msError with the respective error message.
 */
int msHasMemoryAllocationError(const void *buffer) {
    if (buffer == NULL)
        msError("Error caused when allocating memory to buffer.\n");

    return 0;   /* No errors */
}


/**
 *  
 *   this function accepts a standard C string as an input and returns a new msString.\n
 *   This function dynamically allocates memory.
 *   @param str a standard C string to convert to an msString
 *   @return an msString
 */
extern msString msSetString(char *str) {
    void *startMsPtr = NULL;
    char *charMsPtr = NULL;   /* used to point to the start of the character component of the msString */
    int i;
    long long int stringLength = strlen(str);
    long long int memorySize = sizeof(long int) + stringLength;  /* No null terminator, so +1 is not required. sizeof is used
                                                            as long int bit size is different on 32-bit vs 64-bit OS */


    /* Ensure that the msString is <= length of long int otherwise produce an error*/
    if(stringLength > LONG_MAX){
        msError("The resulting msString of your call to msSetString(str), is too large.");
    }

    /* Dynamically allocate memory to msString */
    startMsPtr = (void *) malloc(memorySize);
    msHasMemoryAllocationError(startMsPtr);

    /* Assign the length of the string to the first sizeof(long int) bytes of memory in msString */
    *(long int *) startMsPtr = stringLength;

    /* Assign the characters to memory after the length of the msString */
    charMsPtr = (char *) (startMsPtr + sizeof(long int));
    for (i = 0; i < stringLength; i++) {
        charMsPtr[i] = str[i];
    }

    return (msString) startMsPtr;
}


/**
 *  this function accepts an msString as an input and returns a standard C string.\n
 *  This function dynamically allocates memory.
 *  
 *  @param str the msString to convert to a standard C string
 *  @return a standard C string
 */
extern char *msGetString(msString msStr) {
    char *msStrChPtr = (char *) (msStr + sizeof(long int)); /* Points to first character in msStr */
    char *str = NULL;
    long int msStrLength = msLength(msStr);
    int i;

    /* Dynamically allocate memory to the regular string */
    str = (char *) malloc(msStrLength + 1);  /* +1 for null terminator */
    msHasMemoryAllocationError(str);

    /* Copy the characters in msStr to str */
    for (i = 0; i < msStrLength; i++) {
        str[i] = msStrChPtr[i];
    }
    str[msStrLength] = '\0';

    return str;
}


/**
 *  this function accepts two arguments, a pointer to an msString (the destination) and an msString (the source),
 *  and copies the source value to the destination.\n
 *  This function dynamically re-allocates memory.
 *    
 *  @param msStr the destination msString to copy to
 *  @param msStrToCopy the msString to copy
 */
extern void msCopy(msString *msStr, msString msStrToCopy) {
    long int bufferSize = sizeof(long int) + msLength(msStrToCopy);

    *msStr = realloc(*msStr, bufferSize);   /* Ensure msStr has enough memory to store copied msString */
    memcpy(*msStr, msStrToCopy, bufferSize);
}


/**
 *  this function accepts two inputs, a pointer to an msString (the destination) and an msString (the source),
 *  and concatenates the source value onto the end of the destination.\n
 *  This function dynamically allocates memory.
 *     
 *  @param msStr the destination msString to concatenate the source msString to
 *  @param msStrToCat the source msString to be appended to the end of the destination msString
 */
extern void msConcatenate(msString *msStr, msString msStrToCat) {
    char *strToCat = msGetString(msStrToCat);
    unsigned long int msStrLength = msLength(*msStr);
    unsigned long int strToCatLength = strlen(strToCat);
    unsigned long long int bufferSize =
            sizeof(long int) + msStrLength + strToCatLength;      /* Allow +1 character for null terminator */
    char *endMsStr = NULL;
    int i;

    /* Ensure that the new msString is <= length of long int otherwise produce an error*/
    if(strToCatLength + msStrLength > LONG_MAX){
        msError("The resulting msString of your call to msConcatenate(msStr, msStrToCat), is too large.");
    }

    /* Reallocate memory large enough to store the new concatenated string */
    *msStr = (void *) realloc(*msStr, bufferSize);
    msHasMemoryAllocationError(msStr);

    /* Calculate the pointer to the end of msStr */
    endMsStr = (char *) (*msStr) + sizeof(long int) + msStrLength;

    /* copy the concatenated strings into the memory of msStr */
    for (i = 0; i < strToCatLength; i++)
        endMsStr[i] = strToCat[i];

    /* update the length of msStr */
    *(long int *) (*msStr) = msStrLength + strToCatLength;

    /* Free any dynamically allocated memory no longer in use to prevent memory leaks */
    free(strToCat);
}


/**
 *  this function accepts an msString as an input and returns an integer value that is the
 *  number of characters in the string
 *    
 *  @param msStr the msString variable to find the number of characters in the string
 *  @return an integer equal to the number of characters found in the msString passed as a parameter
 */
extern long int msLength(msString msStr) {
    return *(long int *) msStr;
}


/**
 *  this function accepts two msString values as inputs and returns 0 (zero) if they are identical,
 *  or 1 if they are not.
 *    
 *  @param msStr1 the msString to compare with msStr2
 *  @param msStr2 the msString to compare with msStr1
 *  @return 0 (zero) if the characters making up the strings are the same\n
 *          otherwise returns 1
 */
extern int msCompare(msString msStr1, msString msStr2) {
    char *str1 = msGetString(msStr1);
    char *str2 = msGetString(msStr2);
    int isDifferent = strcmp(str1, str2);

    /* Free dynamically allocated memory to prevent memory leaks */
    free(str1);
    free(str2);

    if (!isDifferent)
        return 0;

    return 1;
}


/**
 *  This function accepts an msStirng value and a standard C string value as inputs and returns 0 (zero)
 *  if the characters making up the strings are the same, or 1 if they are not.
 *    
 *  @param msStr The msString to compare with the standard C string
 *  @param str The standard C string to compare with the msString
 *  @return 0 if the strings making up the characters are the same,\n
 *                 otherwise returns 1
 */
extern int msCompareString(msString msStr, char *str) {
    char *str2 = msGetString(msStr);
    int isDifferent = strcmp(str, str2);

    /* Free dynamically allocated memory */
    free(str2);

    if (!isDifferent)
        return 0;

    return 1;
}


/**
 *  this function accepts a standard C string as input, outputs it as an error message to the user
 *  then exits the program with exit code -1. This function can be called by any of the other msString
 *  functions when an error occurs.
 *     
 *  @param errorMsg the error message to output
 */
extern void msError(char *errorMsg) {
    printf("%s\n", errorMsg);
    fflush(stdin);
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    fflush(stderr);
    exit(-1);
}
