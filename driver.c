/*
 * Application:     Caesar's Cipher
 * File:            driver.c
 * Description:     Source file for driver
 * Language:        C
 * Dev Env:         Arch Linux 64-bit (kernel 5.0.x)
 *
 * Author:          Kyle Thomas
 * Year:            2019
 */


//#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "caesar.h"
#include "parse_file.h"

#define ALPH_FLAG "-a"
#define BOTH_FLAG "-af"
#define BACK_FLAG "-fa"
#define FILE_FLAG "-f"
#define HELP_FLAG "-h"


/* Prints out help when the user doesn't pass in the correct arguments */
void usage(FILE *output) {
    fprintf(output, "caesar shift [option] stringOrFilename\n");
    fprintf(output, "\tOptions:\n\t-f\tTreat stringOrFilename as filename");
    fprintf(output, "(default is string)\n");
    fprintf(output, "\t-a\tOnly perform cipher on letters.\n");
    fprintf(output, "\t-h\tPrint this help message.\n");
    fprintf(output, "example:\n\tcaesar 5 -af sample.txt\n\tcaesar 5 \"sample text\"\n");
    fprintf(output, "\n");
    return;
}


int main(int argc, char **argv)
{
    if (!argv[1]) {
        fprintf(stderr, "Error: Too few arguments.\n");
        usage(stderr);
        exit(EXIT_FAILURE);
    }
    if (!strcmp(argv[1], HELP_FLAG)) {
        usage(stdout);
        exit(EXIT_SUCCESS);
    }
    if (argc < 3) {
        fprintf(stderr, "Error: Too few arguments.\n");
        usage(stderr);
        exit(EXIT_FAILURE);
    } else if (argc > 4) {
        fprintf(stderr, "Error: Too many arguments.\n");
        usage(stderr);
        exit(EXIT_FAILURE);
    }

    int alph_flag = 0;
    int shift = atoi(argv[1]);
    char *str_to_cipher;

    if (!strcmp(argv[2], ALPH_FLAG)) {
        alph_flag = 1;
    } else if (!strcmp(argv[2], FILE_FLAG)) {
        str_to_cipher = malloc(sizeof(char) * BUFF_SIZE);
        parse_file(argv[3], &str_to_cipher);
    } else if ( !strcmp(argv[2], BOTH_FLAG) || !strcmp(argv[2], BOTH_FLAG) ) {
        alph_flag = 1;
        str_to_cipher = malloc(sizeof(char) * BUFF_SIZE);
        parse_file(argv[3], &str_to_cipher);
    } else {
        str_to_cipher = malloc(sizeof(char) * strlen(argv[2]));
        strncpy(str_to_cipher, argv[2], strlen(argv[2]));
    }

    caesar(str_to_cipher, shift, alph_flag);

    free(str_to_cipher);
    exit(EXIT_SUCCESS);
}

