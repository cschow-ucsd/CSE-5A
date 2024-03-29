/*
 * File: hw5b.c
 * Name: Chi Chow
 * Date: September 2nd, 2019
 * Sources of help: None
 *
 * Caesar Cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 81
#define ERROR_MSG_NUM_ARGS "Wrong number of arguments"
#define ERROR_MSG_INV_INT "The argument is not a valid integer"

#define LETTERS "abcdefghijklmnopqrstuvwxyz"

void printErrorMessages(char *message);

void printCipher(int shift, int lowerCase);

void encrypt(int shift, char *input, char *result);

/*
 * Caesar Cipher
 */
int main(int argc, char *argv[])
{
    int shift;
    switch (argc)
    {
        case 2:
            if (sscanf(argv[1], "%d", &shift) != 1) //did not enter an int for shift
            {
                printErrorMessages(ERROR_MSG_INV_INT);
                return 1;
            }
            //print 4 lines of the cipher to demonstrate how it works
            printCipher(0, 1);
            printCipher(shift, 1);
            printf("\n");
            printCipher(0, 0);
            printCipher(shift, 0);
            break;
        case 3:
            if (sscanf(argv[1], "%d", &shift) != 1) //did not enter an int for shift
            {
                printErrorMessages(ERROR_MSG_INV_INT);
                return 1;
            }
            char result[MAX_STR];
            encrypt(shift, argv[2], result);
            printf("%s\n", argv[2]);
            printf("%s\n", result);
            break;
        default: //incorrect number of arguments
            printErrorMessages(ERROR_MSG_NUM_ARGS);
            return 1;
    }

    return 0;
}

/*
 * Shows error message and prints usage of the program.
 */
void printErrorMessages(char *message)
{
    printf("%s\n", message);
    printf("Usage: hw5b <letter shift> [string]\n");
}

/*
 * Prints all letters of the alphabet after shift.
 */
void printCipher(int shift, int lowerCase)
{
    int i, length = strlen(LETTERS);
    while (shift < 0) shift += length; //convert to positive shift (easier to handle)
    for (i = 0; i < length; i++)
    {
        if (lowerCase) //handling lower and upper case letters
        {
            printf("%c", tolower(LETTERS[(i + shift) % length]));
        } else
        {
            printf("%c", toupper(LETTERS[(i + shift) % length]));
        }
    }
    printf("\n");
}

/*
 * Encrypt an input string into result according to shift.
 */
void encrypt(int shift, char *input, char *result)
{
    int i, numLetters = strlen(LETTERS), inputLength = strlen(input);
    while (shift < 0) shift += numLetters; //convert to positive shift (easier to handle)
    for (i = 0; i < inputLength; i++)
    {
        int letterIndex = tolower(input[i]) - 'a';
        if (letterIndex >= 0 && letterIndex < numLetters) //check if it is a letter
        {
            char letter = LETTERS[(letterIndex + shift) % numLetters];
            if (isupper(input[i])) //handling upper lower and upper case letters.
            {
                result[i] = toupper(letter);
            } else if (islower(input[i]))
            {
                result[i] = tolower(letter);
            }
        } else //do not shift if it is not a letter
        {
            result[i] = input[i];
        }
    }
    result[inputLength] = '\0';
}