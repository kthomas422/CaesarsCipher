/*
 * Application:     Caesar's Cipher
 * File:            get_file_contents.c
 * Description:     Source file for get_file_contents
 * Language:        C
 * Dev Env:         Arch Linux 64-bit (kernel 5.0.x)
 *
 * Author:          Kyle Thomas
 * Year:            2019
 */


#include <stdlib.h>
#include <stdio.h>

#include "parse_file.h"


/*
 * Purpose: Opens a file and returns the contents in one big string
 * Args:    The file name
 * Returns: The contents in a string
 */
void parse_file(char *filename, char **buff)
{
    int buff_size = BUFF_SIZE;
    char ch = 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: file %s could not be opened for writing.\n",
                filename);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    for (; (ch = fgetc(fp)) != EOF; ++i) {
        if (buff_size <= i) {
            buff_size *= 2;
            *buff = realloc(*buff, buff_size);
        }
        (*buff)[i] = ch;
    }
    buff[i] = '\0';  // just in case :)
    fclose(fp);
    return;
}

