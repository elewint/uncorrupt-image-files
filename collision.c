/**************************************************************
 *
 *                     collision.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     Implementation of the collision interface. This program checks
 *     whether or not a line's sequence has already been recorded. If
 *     it has, its number data is added into the orig_lines sequence
 *     
 **************************************************************/
 
#include <stdio.h>
#include <seq.h>
#include <atom.h>
#include <table.h>
#include <stdlib.h>
#include <assert.h>
#include <exceptions.h>

/* CheckCollision
 *    Purpose: Detect what the original line is and check whether or not the 
 *             current line is an original line. Add any original lines into 
 *             Seq_T *orig_lines.
 * Parameters: an atom for the current line, a sequence of original lines,
 *             a table with atom for keys and pointer to line_num_data as 
 *             value, a sequence for the current line, and an int for keeping
 *             track whether or not the original line has been found.
 *    Returns: none
 */
void CheckCollision(const char *curr_atom, Seq_T *orig_lines,
            Table_T *collision_table, Seq_T *line_num_data, int *orig_found)
{
    Seq_T *collided = Table_put(*collision_table, curr_atom, line_num_data);
 
    if (collided != NULL) {
        if (*orig_found == 0) {
            Seq_addhi(*orig_lines, collided);
            Seq_addhi(*orig_lines, line_num_data);
            *orig_found = 1;
        }
        else {
            Seq_addhi(*orig_lines, line_num_data);
        }
    }
}