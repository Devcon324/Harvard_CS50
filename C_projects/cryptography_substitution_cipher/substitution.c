#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

string encrypt(string s, string argv[]);

int main(int argc, string argv[])
{
    // Check: only 1 argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check: all entities are letters
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    // Check: there are 26 entities
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check: there are no duplicates
    for (int i = 0, len0 = strlen(argv[1]); i < len0; i++)
    {
        for (int k = i + 1, len1 = strlen(argv[1]); k < len1; k++)
        {
            if (tolower(argv[1][i]) == tolower(argv[1][k]))
            {
                printf("Key contains duplicate = %c and %c.\n", argv[1][i], argv[1][k]);
                return 1;
            }
        }
    }

    string s = get_string("plaintext: ");           // Get Plaintext
    printf("ciphertext: ");                         // begin printing Ciphertext
    encrypt(s, argv);
    return 0;
}

string encrypt(string s, string argv[])
{
    for (int i = 0, len2 = strlen(s); i < len2; i++)
    {
        if (isalpha(s[i]) && isupper(s[i]))         // if it is uppercase,
        {
            int upper = s[i] - 'A';                 // take plaintext char, subtract 'A' to get index position in argv[1][i]
            printf("%c", toupper(argv[1][upper]));  // uppercase the argv[1][i] and print
        }
        else if (isalpha(s[i]) && islower(s[i]))    // if it is lowercase
        {
            int lower = s[i] - 'a';                 // take plaintext char, subtract 'A' to get index position in argv[1][i]
            printf("%c", tolower(argv[1][lower]));  // lowercase the argv[1][i] and print
        }
        else if (!isalpha(s[i]))                    // if it is NOT a letter (punctuation etc.)
        {
            printf("%c", s[i]);                     // then print it unchanged
        }
    }
    printf("\n");                                   // print a new line after finishing printing every char of ciphertext
    return 0;
}