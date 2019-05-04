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


#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "caesar.h"
#include "parse_file.h"


/* Prints out help when the user doesn't pass in the correct arguments */
void usage(void) {
    fprintf(stderr, "caesar shift [option] stringOrFilename\n");
    fprintf(stderr, "\tOptions:\n\t-f\tTreat stringOrFilename as filename");
    fprintf(stderr, "(default is string)\n");
    fprintf(stderr, "\t-a\tOnly perform cipher on letters.\n");
    fprintf(stderr, "\t-h\tPrint this help message.\n");
    return;
}


int main(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "Error: Too few arguments.\n");
        usage();
        exit(EXIT_FAILURE);
    } else if (argc > 5) {
        fprintf(stderr, "Error: Too many arguments.\n");
        usage();
        exit(EXIT_FAILURE);
    }

    int option = 0;
    int alph_flag = 0;
    int shift = atoi(argv[1]);
    char *str_to_cipher;
    char filename[PATH_MAX];
    filename[0] = '\0';

    if (argc == 3) {  // just shift amount and string to shift
        str_to_cipher = malloc(sizeof(char) * strlen(argv[optind]));
        strncpy(str_to_cipher, argv[2], strlen(argv[2]));
    } else {
        while ((option = getopt(argc, argv, "f:ha")) != -1) {
            switch (option) {

                case 'f':
                    strcpy(filename, optarg);
                    str_to_cipher = malloc(sizeof(char) * BUFF_SIZE);
                    parse_file(optarg, &str_to_cipher);
                    break;

                case 'h':
                    usage();
                    exit(EXIT_SUCCESS);

                case 'a':
                    alph_flag = 1;
                    break;
            }
        }
    }

    caesar(str_to_cipher, shift, alph_flag);

    free(str_to_cipher);
    exit(EXIT_SUCCESS);
}

