#include <stdio.h>
#include <cs50.h>

int get_height(void);

//Main method that outputs the hashes and spaces
int main(void)
{
    int height = get_height();

    //Adds a row to the pyramid
    for (int i = 1; i <= height; i++)
    {
        //Adds columns to the pyramid
        for (int j = 1; j <= height * 2 + 2; j++)
        {
            if (j > height - i && j != height + 1 && j != height + 2 && j <= height + 2 + i)
            {
                printf("#");
            }
            else if (j == height + 1 || j == height + 2 || j <= height - i)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

//Prompting the user for the height
int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }

    while (height < 1 || height > 8);

    return height;

}