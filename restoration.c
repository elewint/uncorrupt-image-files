/**************************************************************
 *
 *                     restoration.c
 *
 *     Assignment: filesofpix
 *     Authors:  Eli Intriligator (eintri01), Katie Yang (zyang11)
 *     Date:     Sep 23, 2021
 *
 *     Summary
 *     This program restores corrupted P2 pgm files into "raw" P5 pgm files,
 *     outputting the converted files to standard output.
 *     
 *     Note
 *     Only corrupted plain P2 files are accepted. Other files raise
 *     a checked runtime error.
 *
 *     Properties of the corrupted PGM files this program will convert:
 *     1. The header (magic number, width and height, and maximum 
 *        gray value (Maxval), which is 255) are deleted.
 *     2. Fake image rows are injected to the raster.
 *     3. Whitespace in each row is replaced with a random infusion
 *        of non-digit characters, those that do not encode a digit in ASCII.
 *        The fake rows are also infused with non-digit characters.
 *     4. The infused sequence for original image lines are the same, while
 *        the fake lines does not. 
 *     5. The original images were at least two pixels wide and two pixels 
 *        high
 *
 **************************************************************/
 
#include <stdio.h>
#include <seq.h>
#include <atom.h>
#include <stdlib.h>
#include <ctype.h>

#include <readaline.h>
#include <separator.h>
#include <collision.h>
#include <converter.h>
#include <exceptions.h>

FILE * OpenFile(int argc, char *argv[]);
void ProcessCurrLine(int *line_length_p, char *datapp, FILE *fp, 
                      Seq_T orig_lines, Table_T collision_table);
                     
void free_nds(Seq_T *nds);
void free_orig_lines(Seq_T *orig_lines);
void free_line_num_data(Seq_T *line_num_data);
void free_table(Table_T *collision_table);
void apply(const void *key, void **value, void *cl);

int orig_found = 0;

int main(int argc, char *argv[])
{
    FILE *fp = OpenFile(argc, argv);
    char *datapp = NULL;

    int line_length = 0;
    int *line_length_p = &line_length;
    
    Table_T collision_table = Table_new(500, NULL, NULL);
    Seq_T orig_lines = Seq_new(300);

    do {
        ProcessCurrLine(line_length_p, datapp, fp, orig_lines, 
                                              collision_table);
    } while (*line_length_p != 0);

    converter(&orig_lines);
    
    /* Free memory */
    free_orig_lines(&orig_lines);
    free_table(&collision_table);

    fclose(fp);
    
    /* exit with code of EXIT_SUCCESS */
    exit(EXIT_SUCCESS);
}

/* ProcessCurrLine
 *    Purpose: Separate digit and non-digit. Then store confirmed original
 *             lines into orig_lines.
 * Parameters: an int pointer to current line's length, a char double
 *             pointer to the startof the current line, a file pointer, a
 *             sequence of original lines, and a table for checking
 *             collision.
 *             
 *    Returns: void
 *
 *       Note: 
 *
 */
void ProcessCurrLine(int *line_length_p, char *datapp, FILE *fp,
                      Seq_T orig_lines, Table_T collision_table)
{
    *line_length_p = readaline(fp, &datapp);
    *line_length_p /= sizeof(char);
    
    /* If EOF is reached */
    if (*line_length_p == 0){
        return;
    }

    Seq_T *line_num_data = malloc(sizeof(Seq_T));
    CheckMemoryAlloc(line_num_data);

    *line_num_data = Seq_new(70);
    Seq_T nds = Seq_new(1000);
    
    /* separate digit from non-digit characters */
    const char *curr_atom = separator(&datapp, *line_length_p, &nds, 
                                                      line_num_data);

    /* check collision of the infused sequence */
    CheckCollision(curr_atom, &orig_lines, &collision_table,
                                 line_num_data, &orig_found);

    free_nds(&nds);
    free(datapp);
}

/* OpenFile
 *    Purpose: Attempts to open a file from the command line, throwing errors
 *             in the three cases described below.
 * Parameters: number of command line arguments as an int and the
 *             characters of each argument as a char array
 *    Returns: A file pointer for the file.
 *
 *       Note: Throws a checked runtime error if
 *             1. More than one argument is supplied
 *             2. The named input file cannot be opened
 *             3. An error is encountered reading from an input file
 */
FILE *OpenFile(int argc, char *argv[])
{
    if(argc > 2) {
        RAISE(TooManyArgs);
    }

    /*
     * set file pointer to stdin to handle command line input in the case
     * that no file is supplied
    */
    FILE *fp;
    fp = stdin;

    /*
     * if a file is supplied as an argument, open the file and make fp 
     * point to the opened filestream
    */
    if (argc == 2) {
        fp = fopen(argv[1], "r");
    }

    /* check if the file opened successfully */
    if (fp == NULL){
        RAISE(FileFail);
    }
    
    return fp;
}

/* free_nds
 *    Purpose: Frees memory used to store infused non-digit characters
 * Parameters: A sequence of the infused non-digit characters
 *    Returns: void
 */
void free_nds(Seq_T *nds)
{
    int nds_length = Seq_length(*nds);

    for (int i = 0; i < nds_length; i++) {
        Seq_T curr_char = Seq_get(*nds, i);
        free(curr_char);
    }

    Seq_free(nds);
}

/* free_orig_lines
 *    Purpose: Free the memory used to store the original lines.
 * Parameters: Pointer to a sequence of the original lines.
 *    Returns: void
 */
void free_orig_lines(Seq_T *orig_lines)
{
    int length = Seq_length(*orig_lines); 

    /*
     * Free all line_num_data sequences except the last, since the last
     * is also stored in the table and will be freed by free_table
     */
    for (int i = 0; i < length - 1; i++) {
        Seq_T * curr_line_num_data = Seq_get(*orig_lines, i);
        free_line_num_data(curr_line_num_data);
    }

    Seq_free(orig_lines);
}

/* free_line_num_data
 *    Purpose: Frees the memory used to store the numbers on each line
 * Parameters: Pointer to the sequence of the line's number data
 *    Returns: void
 */
void free_line_num_data(Seq_T *line_num_data)
{
    int width = Seq_length(*line_num_data); 

    /* free the memory used to store each number */
    for (int j = 0; j < width; j++) {
        Seq_T *curr_num = Seq_get(*line_num_data, j);
        int curr_num_length = Seq_length(*curr_num);
        (void)curr_num_length;
        
        /* free the memory used for each digit */
        for (int k = 0; k < curr_num_length; k++) {
            int *curr_digit = Seq_get(*curr_num, k);
            free(curr_digit);
        }
        
        Seq_free(curr_num);
        free(curr_num);
    }

    Seq_free(line_num_data);
    free(line_num_data);
}

/* free_table
 *    Purpose: Frees the memory associated with Hanson Table and the sequences
 *             stored in each value of the table
 * Parameters: Pointer to a Hanson Table
 *    Returns: void
 */
void free_table(Table_T *collision_table)
{
    Table_map(*collision_table, apply, NULL);

    Table_free(collision_table);
}

/* apply
 * Purpose: Mapping function to free the memory stored in each value
 *          of the Hanson Table
 * Parameters: a constant void pointer for the current key of the table, a
 *             void double pointer for the value of the table, and a void
 *             pointer for the function's closure.
 *    Returns: void
 */
void apply(const void *key, void **value, void *cl)
{
    (void) key;
    (void) cl;

    Seq_T *line_num_data = *value;
    free_line_num_data(line_num_data);
}
