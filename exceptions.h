/**************************************************************
 *
 *                     exceptions.h
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     The exceptions interface.
 *     Stores exceptions used for the program.
 *
 *     Note
 *     Exceptions for
 *     1. Either or both of the supplied args are null
 *     2. More than one argument supplied
 *     3. Memory allocation with malloc failed
 *     4. Problem opening the file
 *
 **************************************************************/
 
#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <stdlib.h>
#include <stdio.h>
#include <except.h>

Except_T ArgsNull;
Except_T TooManyArgs;
Except_T MemoryAllocFail;
Except_T FileFail;

void CheckMemoryAlloc(void * input_ptr);

#endif /* __EXCEPTIONS */