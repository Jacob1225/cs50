#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//Calling defined methods
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

//Main Method that outputs the reading level
int main(void)
{
    string text = get_string("Text: ");

    int length = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float l = ((float) length / (float) words) * 100;
    float s = ((float) sentences / (float) words) * 100;

    //Coleman-Liau index of text
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    //Validating the reading level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//Method that counts the number of letters in the input text
int count_letters(string text)
{
    int n = strlen(text);
    int count = 0;

    //Validating if the char is a lower or uppercase letter
    for (int i = 0; i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

//Method that count the number of words in the input text
int count_words(string text)
{
    int n = strlen(text);
    int count = 0;

    //Validating if the char is a space or the last word of the text
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ' || i == n - 1)
        {
            count++;
        }
    }
    return count;
}

//Method that counts the number of sentences in the input text
int count_sentences(string text)
{
    int n = strlen(text);
    int count = 0;

    //Validating if the text has punctuation to seperate sentences
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}


