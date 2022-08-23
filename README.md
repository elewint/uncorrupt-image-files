----------------------------------------------------------------------
|                      COMP 40 hw01: Uncorrupt Image Files           |
| Eli Intriligator (eintri01)                                        |
| Katie Yang (zyang11)                                               |
| Sep 23 2021                                                        |
----------------------------------------------------------------------

Help acknowledgements:
TAs: Alex, Dylan, Tina, Ann-Marie, Zach, Jackson, Liana, Igor, Gustavo
     Mary-Joy

Features implemented & existing problems

Correctly implemented:

1. readaline reads in each line of the file and returns the size of that
   line in bytes
2. separator separates digits (numbers from 0 to 9) from non-digit
   characters from the ISO Latin-1 extended ASCII table
3. collision finds the sequence injected to original lines and stores the
   original lines
4. converter converts stored digits into their char equivalents and
   outputs to standard output with the correct header added in
5. Resulting raw pgm opens correctly. The program successfully decorrupts
   all of the supplied corrupted pgms.
6. readaline can read in a line of any length, dynamically allocating memory
   on the heap for the input line.

Existing problems/limitations:
1. If an uncorrupted file is supplied (for example a completely normal P2 pgm
   file) the injected image line would have a repeated injection sequence,
   so the program would not raise a C.R.E.

Time spent:
58 hrs as of submission
