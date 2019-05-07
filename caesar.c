/*
 * Application:     Caesar's Cipher
 * File:            caesar.c
 * Description:     Source file for caesar
 * Language:        C
 * Dev Env:         Arch Linux 64-bit (kernel 5.0.x)
 *
 * Author:          Kyle Thomas
 * Year:            2019
*/


#include <stdio.h>
#include <string.h>

#include "caesar.h"

#define ASCII_LOWER         33   // lowest printable ascii char (!)
#define ASCII_UPPER         126  // heighest printable ascii char (~)
#define MAX_ASCII_SHIFT     94   // 95 printable ascii characters
#define LETTERS_LOWER       97   // a
#define LETTERS_UPPER       122  // z
#define MAX_LETTERS_SHIFT   26   // letters in alphabet
#define CASE_DIFF           32   // difference from A -> a or Z -> z
#define CAPITAL_LOWER       65   // A
#define CAPITAL_UPPER       90   // Z


/*
 * Purpose: Makes sure the shift is withing the correct bounds, if not then
 *          it will alter it so it "wraps" back around
 * Args:    The shift amound whether only the alphabet or not is being used
 * Returns: None
 */
void validate_shift(int *shift, const int alphabet_flag)
{
    int max_shift = 0;
    if (alphabet_flag)
        max_shift = MAX_LETTERS_SHIFT;
    else
        max_shift = MAX_ASCII_SHIFT;

    if (*shift > max_shift) {
        *shift = *shift % max_shift;
        fprintf(stderr, "Warning: shift cannot be over %d\n", max_shift);
        fprintf(stderr, "\tSetting shift to %d\n", *shift);
    } else if (*shift < -max_shift) {
        *shift = *shift % -max_shift;
        fprintf(stderr, "Warning: shift cannot be under %d\n", -max_shift);
        fprintf(stderr, "\tSetting shift to %d\n", *shift);
    }

    return;
}


/*
 * Purpose: Shift the characters in the string passed in to perform the cipher
 *          If the alph flag is set, then letters are converted to lowercase
 *          and only those are shifted (within lowercase letters)
 *
 * Args:    The string to change, the amount to shift the characters and if
 *          "alphabet_flag" is true then ignore any charactre that is not a
 *          letter, otherwise shift all characters 
 *          (such as spaces and punctuation).
 * Returns: None
 */
void caesar(char *string, int shift, const int alphabet_flag)
{
    validate_shift(&shift, alphabet_flag);
    int upper = 0;
    int lower = 0;
    int max_shift = 0;
    int tmp_letter = 0;
    if (alphabet_flag) {
        max_shift = MAX_LETTERS_SHIFT;
        upper = LETTERS_UPPER;
        lower = LETTERS_LOWER;
    } else {
        max_shift = MAX_ASCII_SHIFT;
        upper = ASCII_UPPER;
        lower = ASCII_LOWER;
    }

    for (int i = 0; string[i]; ++i) {
        if (alphabet_flag) {  // turn uppercase letters to lowercase
            if ( (string[i] >= CAPITAL_LOWER) && (string[i] <= CAPITAL_UPPER) )
                string[i] += CASE_DIFF;
        }
#if 1
        if ( (string[i] >= lower) && (string[i] <= upper) ) {
            tmp_letter = string[i] + shift;
            if (tmp_letter > upper)  // overflow, loop back to beginning
                tmp_letter -= max_shift;
            else if (tmp_letter < lower)  // lower, loop around to end
                tmp_letter += max_shift;
            string[i] = tmp_letter;
        }
#endif
#if 0
        // shift alphabet characters and ignore the rest
        if ( (string[i] >= lower) && (string[i] <= upper) ) {
            string[i] += shift;
            if (string[i] > upper)  // overflow, loop back to beginning
                string[i] -= max_shift;
            else if (string[i] < lower)  // underflow, loop back to end
                string[i] += max_shift;
        }
#endif
    }
    printf("%s\n", string);
    return;
}

