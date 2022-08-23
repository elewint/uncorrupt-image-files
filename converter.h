/**************************************************************
 *
 *                     converter.h
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     The converter interface.
 *
 **************************************************************/
 
#ifndef __CONVERTER__
#define __CONVERTER__

#include <seq.h>
#include <atom.h>
#include <table.h>
#include <stdlib.h>
#include <assert.h>

void converter(Seq_T *orig_lines);
void PrintHeader(int height, int width);

#endif /* __CONVERTER */