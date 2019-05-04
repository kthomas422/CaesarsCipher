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


/*
 * Purpose: Makes sure the shift is withing the correct bounds, if not then
 *          it will alter it so it "wraps" back around
 * Args:    The shift amound whether only the alphabet or not is being used
 * Returns: None
 */
void validate_shift(int *shift, const int alphabet_flag)
{
    if (alphabet_flag) {
        ;
    } else {
        if (*shift > 95) {
            while (*shift > 95)
                *shift -= 95;
            fprintf(stderr, "Warning: shift cannot be greater than 95...\n \
                    Setting shift to %d\n", *shift);
        } else if (*shift < -95) {
            while (*shift < -95)
                *shift += 95;
            fprintf(stderr, "Warning: shift cannot be less than -95...\n \
                    Setting shift to %d\n", *shift);
        }
    }
    return;
}


/*
 * Purpose: Shift the characters in the string passed in to perform the cipher
 * Args:    The string to change, the amount to shift the characters and if
 *          "alphabet_flag" is true then ignore any charactre that is not a
 *          letter, otherwise shift all characters 
 *          (such as spaces and punctuation).
 * Returns: None
 */
void caesar(char *string, int shift, int alphabet_flag)
{
    validate_shift(&shift, alphabet_flag);
    if (alphabet_flag) {
        ;
    } else {
        for (int i = 0; string[i]; ++i)
            string[i] += shift;
    }
    printf("%s\n", string);
    return;
}

