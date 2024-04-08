#include "task1.h"
#include "task2.h"
#include "msString.h"
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    test_task1();
    test_task2(argv);


    printf("\n--Task 3--\n");
    /* Task 3 Test Code 1 - Given in spec */

    /* Functions that return values that have been dynamically allocated memory are stored as variables, rather than
     * being called within the printf function. This allows their memory to be freed after use to prevent memory leaks.
     * The msLength function does not need to be set equal to a variable, as the variable returned by it has
     * statically allocated memory */
    char *msAsString = NULL;
    char *msCopyAsString = NULL;
    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World!");
    msString mscopy = NULL;
    msCopy(&mscopy, ms);
    msCopyAsString = msGetString(mscopy);
    msAsString = msGetString(ms);

    /* The following 8 printf statements are used to test the msString datatype & its functions */
    printf("String |%s| is %ld characters long (%p).\n", msAsString, msLength(ms), ms);
    printf("Copied string |%s| is %ld characters long (%p).\n", msCopyAsString, msLength(mscopy), mscopy);

    printf("Compare ms with mscopy : %d \n", msCompare(ms, mscopy));
    printf("Compare ms with ms2 : %d \n", msCompare(ms, ms2));
    printf("Compare ms with Hello : %d \n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX : %d \n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella : %d \n", msCompareString(ms, "Hella"));

    msConcatenate(&mscopy, ms2);
    free(msCopyAsString);   /* Prevent a memory leak by deallocating the prior assigned memory */
    msCopyAsString = msGetString(mscopy);
    printf("Concatenated string |%s| is %ld characters long (%p).\n", msCopyAsString, msLength(mscopy), mscopy);

    /* Prevent a memory leak by deallocating dynamically assigned memory */
    free(ms);
    free(ms2);
    free(mscopy);
    free(msCopyAsString);
    free(msAsString);



    /* Task 3 Test Code 2 - My own tests */

    /* check that an original string and its corresponding msString's getString produces the same string with the
     * exact same length */
    char* originalString = "Hiya!";
    msString testMs = msSetString(originalString);
    char* testMsAsString = msGetString(testMs);

    printf("original string: |%s|, corresponding msString's resulting getString: |%s|\n", originalString, testMsAsString);
    printf("original string length: |%llu|, corresponding msString msLength: |%ld|\n", strlen(originalString), msLength(testMs));

    /* Free dynamically assigned memory to prevent memory leaks */
    free(testMs);
    free(testMsAsString);

    return 0;
}
