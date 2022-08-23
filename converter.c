/**************************************************************
 *
 *                     converter.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     Implementation of the converter interface. It converts the
 *     lines stored in orig_lines into their char equivalents and
 *     outputs them to standard output with correct header added in.
 *
 *     Note
 *     Header consists of the magic number P5, width and height of the
 *     original image, and maximum gray value (Maxval), which is 255.
 *
 **************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <seq.h>
#include <converter.h>
#include <exceptions.h>

/* converter
 *    Purpose: Convert numbers stored in original lines to binary and
 *             print as chars to standard output with correct header added on.
 * Parameters: A sequence of original lines.
 *    Returns: none
 *
 *       Note: Header consists of the magic number P5, width and height of the
 *             original image, and maximum gray value (Maxval), which is 255.
 *             
 */
void converter(Seq_T *orig_lines)
{
    Seq_T *first_line_num_data = Seq_get(*orig_lines, 0);
    int length = Seq_length(*orig_lines);
    int width = Seq_length(*first_line_num_data);

    assert(length >= 2);
    assert(width >= 2);

    PrintHeader(length, width);

    for (int i = 0; i < length; i++) {
        Seq_T *curr_line_num_data = Seq_get(*orig_lines, i);

        for (int j = 0; j < width; j++) {
            Seq_T *curr_num = Seq_get(*curr_line_num_data, j);
            int curr_num_length = Seq_length(*curr_num);

            char *curr_num_digits = calloc(curr_num_length,
                                           sizeof curr_num_digits);
            CheckMemoryAlloc(curr_num_digits);
            
            for (int k = 0; k < curr_num_length; k++) {
                char *curr_digit = Seq_get(*curr_num, k);
                *curr_digit += '0';
                curr_num_digits[k] = *curr_digit;
            }
            
            int num_as_int = atoi(curr_num_digits);
            
            assert(num_as_int <= 255);
            assert(num_as_int >= 0);

            putchar(num_as_int);
            free(curr_num_digits);
        }
    }
}

/* PrintHeader
 *    Purpose: Print header to standard output.
 * Parameters: two ints for the height and width of the original image
 *    Returns: none
 *
 *       Note: Header consists of the magic number P5, width and height of the
 *             original image, and maximum gray value (Maxval), which is 255.
 */
void PrintHeader(int height, int width)
{
    printf("P5\n");
    printf("%d", width);
    printf("\n");
    printf("%d", height);
    printf("\n");
    printf("255\n");
}