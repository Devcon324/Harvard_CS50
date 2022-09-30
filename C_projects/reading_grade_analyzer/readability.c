#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string reading_grade(string phrase);                        //declare function

int main(void)
{
    string phrase = get_string("Text: ");                   //get input
    printf("%s\n", reading_grade(phrase));                  //print answer using function
}

string reading_grade(string phrase)                         //function to calculate and compute grade level for this assignment
{
    string ans = "";                                        //placeholder to return a string
    int words = 0, sentences = 0, letters = 0;
    for (int i = 0, n = strlen(phrase); i < n; i++)         //go through each char in string array
    {
        //Word = letter followed by space = word
        //OR
        //Word = letter OR punctuation followed by \0, i.e end of string
        if ((phrase[i] == ' ') || ((isalpha(phrase[i]) || ispunct(phrase[i])) && phrase[i + 1] == '\0'))
        {
            words++;
        }
        if (phrase[i] == '.' || phrase[i] == '!' || phrase[i] == '?') //check for punctuation for sentence count
        {
            sentences++;
        }
        if (isalpha(phrase[i]))                             //check for chars for letter count
        {
            letters++;
        }
    }
    float avgS  = (float) sentences / words * 100;              //compute avg sentences per 100 words
    float avgL  = (float) letters / words * 100;                //compute avg letters per 100 words
    int index   = round(0.0588 * avgL - 0.296 * avgS - 15.8);   //Coleman-Liau index
    if (index >= 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", index);
    }
    return ans;
}