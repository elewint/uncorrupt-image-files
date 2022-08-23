/**************************************************************
 *
 *                     readaline.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     Implementation of the readaline interface. Reads a single
 *     line of input from the file pointer, placing the characters
 *     comprising the line into a contiguous array of bytes.
 *
 *     Note
 *     
 *
 **************************************************************/
 
#include <stdio.h>
#include <readaline.h>
#include <stdlib.h>
#include <except.h>

/* readaline
 *    Purpose: Read the current line and store information in datapp.
 * Parameters: File pointer for the input filestream and a char double pointer
 *             which will be point to the start of the input line
 *    Returns: the size of the input line in bytes
 *
 *       Note: The caller of readaline should free the array. readaline leaves
 *             the file seek pointer at the first character of the following
 *             line (if any) or at EOF. 
 *
 *             Throws a checked runtime error if:
 *             1. Either or both of the supplied arguments is NULL 
 *             2. An error is encountered reading from the file
 *             3. Memory allocation fails
 * 
 *             The initial capacity of datapp is 1000. If the line exceeds
 *             that number of characters, the capacity is doubled.
 *
 */
size_t readaline(FILE *inputfd, char **datapp)
{
    int capacity = 1000;

    /*
    * Raise an exception if either (or both) or the arguments are null,
    * or if reading from file fails.
    */
    if (inputfd == NULL || datapp == NULL) {
        Except_T ArgsNull = {"Either or both of the supplied args are null"};
        RAISE(ArgsNull);
    }

    char input_char = getc(inputfd);

    /*
    * If readaline is called when there are no more lines to be read, set
    * *datapp to NULL and return 0.
    */
    if (feof(inputfd))
    {
        datapp = NULL;
        return 0;
    }

    /* Allocate memory for an array of characters of size capacity */
    *datapp = malloc(sizeof datapp * capacity);

    /* Raise C.R.E if memory allocation fails */
    if (datapp == NULL){
        Except_T MemoryAllocFail = {"Failed to allocate memory using malloc"};
        RAISE(MemoryAllocFail);
    }

    int line_length = 0;

    /*
     * Continue to read characters into the array until we reach the
     * newline character or end of the file
     */
    while(input_char != '\n'){
        if (line_length == capacity - 1){
            *datapp = realloc(*datapp, sizeof datapp * capacity * 2);
            capacity *= 2;
        }

        (*datapp)[line_length] = input_char;
        input_char = getc(inputfd);
        line_length++;

        /* Check EOF condition */
        if (feof(inputfd)) {
            return 0;
        }
    }
    
    return line_length * sizeof(char);
}
