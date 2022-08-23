/**************************************************************
 *
 *                     separator.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     Implementation of the separator interface. This program
 *     separates digits from non-digit characters and stores
 *     the extracted characters in sequences
 *
 *     Note
 *     Digit characters are stored in sequences depicting numbers, which are
 *     themselves stored in the line_num_data sequence. Non-digits 
 *     are stored in the nds sequence
 *
 **************************************************************/
 
#include <stdio.h>
#include <seq.h>
#include <atom.h>
#include <stdlib.h>
#include <ctype.h>
#include <separator.h>
#include <exceptions.h>

/* separator
 *    Purpose: separates digits from non-digit characters and stores
 *             the extracted characters in the parameter sequences
 * Parameters: a char double pointer to the start of the current line,
 *             an int for the length of this line, a sequence for storing the 
 *             current line's non-digit characters, and a sequence for
 *             storing the current line's digit sequences.
 *             
 *    Returns: An atom created for the infused non-digit characters.
 */
const char *separator(char **first, int length, Seq_T *nds,
                                      Seq_T *line_num_data)
{
    int nds_index = 0, line_num = 0, last_char_int = 0;
    int *last_char_int_p = &last_char_int;

    for (int i = 0; i < length; i++) {
        char curr_char = (*first)[i];
        /* if curr char is an integer*/
        if (isdigit(curr_char)) {
            AddToLineNumData (last_char_int_p, line_num_data, line_num,
                                                             curr_char);
        }
        /* if curr char is not an integer */
        else {
            char *curr_nondigit = malloc(sizeof curr_nondigit);
            CheckMemoryAlloc(curr_nondigit);

            *curr_nondigit = curr_char;
            Seq_addhi(*nds, curr_nondigit);
            nds_index++;

            if (last_char_int == 1) {
                line_num += 1;
            }

            last_char_int = 0;
        }
    }
    
    return CreateAtom(nds, nds_index);
}

/* AddToLineNumData
 *    Purpose: Add current char to the current line_num_data. 
 * Parameters: an int pointer to whether or not the last char is an integer,
 *             a sequence of current line num data, an int for the line
 *             number, and an int for the current character.
 *             
 *    Returns: void
 *
 */
void AddToLineNumData(int *last_char_int_p, Seq_T *line_num_data, 
                                     int line_num, int curr_char)
{
    int *curr_digit = malloc(sizeof curr_digit);
    CheckMemoryAlloc(curr_digit);
    *curr_digit = curr_char - 48;

    /* 
     * If previous char was a digit, append current digit to
     * the same number
     */
    if (*last_char_int_p > 0) {
        /* Add current digit to ongoing number */
        Seq_T *curr_number = Seq_get(*line_num_data, line_num);
        Seq_addhi(*curr_number, curr_digit);
    }
    /* 
     * If previous char was not a digit, this means we are
     * starting a new number
     */
    else {
        Seq_T *new_number = malloc(sizeof(Seq_T));
        CheckMemoryAlloc(new_number);

        *new_number = Seq_new(1);
        Seq_addhi(*new_number, curr_digit);
        Seq_addhi(*line_num_data, new_number);
        *last_char_int_p = 1;
    }
}

/* CreateAtom
 *    Purpose: Create an atom for current line's infused non-digit characters
 * Parameters: ptr to a sequence storing the current non-digit characters,
 *             and an int for the length of that sequence.
 *             
 *    Returns: An atom created for the infused non-digit characters.
 *
 *       Note:
 */
const char *CreateAtom(Seq_T * nds, int length)
{
    char *char_nds = malloc(sizeof char_nds *length);
    CheckMemoryAlloc(char_nds);
    
    for (int i = 0; i < length; i++) {
        char * char_ptr = Seq_get(*nds, i);

        /* 
         * Replace any null chars with the digit 0 so the atom
         * doesn't read it as a terminator 
         */
        if (*char_ptr == '\0') {
            *char_ptr = '0';
        }

        char_nds[i] = *char_ptr;
    }

    const char *curr_atom = Atom_new(char_nds, length);
    
    free(char_nds);

    return curr_atom;
}
