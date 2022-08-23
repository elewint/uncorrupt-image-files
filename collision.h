/**************************************************************
 *
 *                     collision.h
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     The collision interface.
 *
 **************************************************************/

#ifndef __COLLISION__
#define __COLLISION__

#include <stdio.h>
#include <seq.h>
#include <atom.h>
#include <table.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

void CheckCollision(const char *curr_atom, Seq_T *orig_lines,
                    Table_T * collision_table, Seq_T *line_num_data, 
                    int * orig_found);

#endif /* __COLLISION */
