/**************************************************************
 *
 *                     separator.h
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     The separator interface.
 *
 **************************************************************/
 
#ifndef __SEPARATOR__
#define __SEPARATOR__

#include <stdio.h>
#include <seq.h>
#include <atom.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

const char *separator(char **first, int length, Seq_T *nds, 
                                      Seq_T *line_num_data);
const char *CreateAtom(Seq_T *nds, int length);
void AddToLineNumData(int *last_char_int_p, Seq_T *line_num_data, 
                                     int line_num, int curr_char);

#endif /* __SEPARATOR__ */
