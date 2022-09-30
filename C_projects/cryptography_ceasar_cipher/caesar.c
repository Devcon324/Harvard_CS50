#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // accept a single command-line argument with 1 argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // accept a non-negative integer
    // loop through each char or element in argv[1]
    // if it is non-integer OR negative, show usage
    for (int j = 0, m = strlen(argv[1]); j < m; j++)
    {
        if ((!isdigit(argv[1][j])) || (argv[1] < 0))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]); // turn argv[1] from string to int called "key"
    string text = get_string("plaintext: "); // get user input for plain text

    // loop through each element in plaintext
    // if "key = 27", 'A' should not become '['
    // to use the equasion, we need to zero the plaintext char in terms of caesar
    // this means A = 65 must become A = 0, B = 1, Z = 25
    // then we can add the key and take modulous of 26
    // then add back the relevant ASCII increment depending if char is upper or lower case
    // ex. (when key = 1)
    // D = 68, E = 69
    // (((68 - 65) + key) % 26) + 65 = 69
    // no overflow ex. (when key = 1)
    // Z = 90, A = 65
    // (((90 - 65) + key) % 26) + 65 = 65

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = (((text[i] - 65) + key) % 26) + 65;
        }
        if (islower(text[i]))
        {
            text[i] = (((text[i] - 97) + key) % 26) + 97;
        }
    }

    printf("ciphertext: %s\n", text);
}
