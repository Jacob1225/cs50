#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Defining helper methods
bool validate_key(string s);
void get_indicies(string s, string key);

//Main method that encrypts a plain text string
int main(int argc, string argv[])
{
    //Validates if only one argument was entered by the user
    if (argc == 2)
    {
        //Validates if a valid key was entered by the user
        if (validate_key(argv[1]) == true)
        {
            string text = get_string("plaintext: ");
            int length = strlen(text);
            printf("a: %i\n", length);
            char ciphertext[length];
            string key = argv[1];

            //Loop through the plaintext string
            for (int i = 0; i < length; i++)
            {
                int index = 0;
                if (isalpha(text[i]) == 0)
                {

                    ciphertext[i] = text[i];
                }
                else
                {
                    for (char c = 'a'; c <= 'z'; c++)
                    {
                        if (tolower(text[i]) == c)
                        {
                            //Validates if input character is uppercase
                            if (isupper(text[i]))
                            {

                                ciphertext[i] = toupper(key[index]);
                                break;
                            }
                            //Validates if character of plaintext is lowercase
                            else
                            {
                                ciphertext[i] = tolower(key[index]);
                                break;
                            }
                        }
                        index++;
                    }
                }
            }


            printf("length: %lu\n", strlen(ciphertext));
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
        //validates if the input key is invalid
        else
        {
            printf("Key must be 26 characters long with no duplicates or special characters\n");
            return 1;
        }
    }

    //if the user did not input one argument only
    else
    {
        printf("Must provide one and only one key\n");
        return 1;
    }

}

//Method that validates if the key is valid and returns true or false
bool validate_key(string s)
{
    int n = strlen(s);
    int count = 0;

    //Validates that the key has 26 characters
    if (n == 26)
    {
        //Loops through the alphabet
        for (char c = 'a'; c <= 'z'; c++)
        {
            for (int i = 0; i < 26; i++)
            {
                //If the character from the key matches the character from the alphabet
                if (tolower(s[i]) == c)
                {
                    count++;
                    break;
                }
            }
        }
        //Valid key if the count is 26
        if (count == 26)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else
    {
        return false;
    }
}
