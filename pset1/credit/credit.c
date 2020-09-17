#include <stdio.h>
#include <cs50.h>

//Calling methods defined after the main method
long get_credit_number(void);
int get_length(long n);
void get_card_type(long n);
int get_digit_sum(long num);
int get_first_digits(long num);
int get_digits(long num);

//Main method of the program that calls all other methods
int main(void)
{
    long number = get_credit_number();
    long copy = number;
    int sumDigits = get_digit_sum(number);
    int count = 1;
    int checkSum = 0;

    //Looping through the digits and adding every second digit to the checkSum afterwards
    do
    {
        //Validates if digits is every second one
        if (count % 2 == 0)
        {
            int r = 2 * (number % 10);

            if (get_length(r) > 1)
            {
                do 
                {
                    checkSum += r % 10;
                    r = r / 10;
                }
                while (r > 0);
            }
            else
            {
                checkSum += r;
            }

        }
        number = number / 10;
        count ++;
    }
    while (number > 0);

    //Adding the sum of the digits that were not multiplied by 2 to the checkSum
    checkSum += sumDigits;

    //Validating if the last digit of the check sum is 0
    checkSum % 10 != 0 ? printf("INVALID\n") : get_card_type(copy);

}
//Method that prompts the user for a credit card number
long get_credit_number(void)
{
    long number;

    //Prompting the user until they input a positive number
    do
    {
        number = get_long("Number: ");
    }

    while (number < 0);

    return number;
}

//Method that returns the length of each product
int get_length(long n)
{
    int count = 0;

    do
    {
        n = n / 10;
        count++;
    }
    while (n > 0);

    return count;
}

//Method that returns the sum of each digit not multiplied by 2
int get_digit_sum(long num)
{
    int count = 1;
    int sum = 0;

    //Looping through digits and adding every second digit to the sum variable
    do
    {
        if (count % 2 != 0)
        {
            sum += num % 10;
        }
        num = num / 10;
        count ++;
    }
    while (num > 0);

    return sum;
}
//Method that prints the type of credit card
void get_card_type(long n)
{
    int count = 0;
    long copy = n;
    int digit;
    string type = "";


    do
    {
        count++;
        digit = n % 10;
        n = n / 10;
    }
    while (n > 0);

    //Verifying if card is of type AMEX
    if (count == 15 && (get_digits(copy) == 34 || get_digits(copy) == 37))
    {
        type = "AMEX";
    }
    //Verifying if card is of type VISA
    else if (count == 13 && get_first_digits(copy) == 4)
    {
        type = "VISA";
    }
    //Verifying if card is of type VISA or MASTERCARD
    else if (count == 16)
    {
        if (get_first_digits(copy) == 4)
        {
            type = "VISA";
        }
        //Verifying if card is of type MASTERCARD
        else if (get_digits(copy) == 51 || get_digits(copy) == 52 || get_digits(copy) == 53 || get_digits(copy) == 54
                 || get_digits(copy) == 55)
        {
            type = "MASTERCARD";
        }
        else
        {
            type = "INVALID";
        }
    }
    else
    {
        type = "INVALID";
    }

    printf("%s\n", type);
}

//Method that returns the first two digits of the credit card number
int get_digits(long num)
{
    do
    {
        num /= 10;
    }
    while (num >= 100);
    return num;
}

//Method that returns the first digit of the credit card number
int get_first_digits(long num)
{
    do
    {
        num /= 10;
    }
    while (num >= 10);
    return num;
}