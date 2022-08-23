/**************************************************************
 *
 *                     exceptions.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     Implementation of the exceptions interface.
 *     Stores exceptions used for the program.
 *
 **************************************************************/
 
#include <stdlib.h>
#include <stdio.h>
#include <exceptions.h>

/* C.R.E when argument(s) are NULL */
Except_T ArgsNull = {"Either or both of the supplied args are null"};
/* C.R.E when more than one argument is supplied */
Except_T TooManyArgs = {"More than one argument supplied"};
/* C.R.E when memory allocatio failed */
Except_T MemoryAllocFail = {"Failed to allocate memory using malloc"};
/* C.R.E when problem encountered when opeing file */
Except_T FileFail = {"Problem opening the file"};

void CheckMemoryAlloc(void * input_ptr)
{
    if (input_ptr == NULL) {
        RAISE(MemoryAllocFail);
    }
}
