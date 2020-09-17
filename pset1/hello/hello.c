#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Storing the users name as a string in a variable called name
    string name = get_string("What is your name\n");

    printf("Hello %s\n", name);
}

