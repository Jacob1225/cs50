from cs50 import get_int
# Function that prompts user for credit number


def get_number():

    number = get_int("Number: ")
    return number

# Function that returns the first 2 digits of the card


def get_digits(number):
    while number >= 100:
        number = number / 10
    return number

# Function that returns the first digit of a credit card


def get_digit(number):
    while number >= 10:
        number = int(number / 10)
    return number

# Function that determines if credit card number is valid


def credit():

    # Get the credit card number
    number = get_number()
    checkSum = 0
    count = 0

    # Make a copy of the credit card number
    cardCopy = number

    # Store first two digits of card for type checking
    digits = int(get_digits(cardCopy))

    # Looping through the digits and adding every second digit to the checkSum afterwards
    while number > 0:
        count += 1

        # If even digit multiply the remainder by 2 and add the product digits to checkSum
        if count % 2 == 0:
            r = 2 * int(number % 10)

            # If r has more than one digit then add all digits to checkSum
            if len(str(r)) > 1:
                while r > 0:
                    checkSum += int(r % 10)
                    r = int(r / 10)
            else:
                checkSum += r

        # If odd digit then add remainder to checkSum
        else:
            checkSum += int(number % 10)

        number = int(number / 10)

    # Verfiy if the card is an AMEX
    if count == 15 and (digits == 34 or digits == 37):
        card = "AMEX"

    # Verify if card is of type VISA
    elif get_digit(cardCopy) == 4 and (count == 13 or count == 16):
        card = "VISA"

    # Verify if card is of type MASTERCARD
    elif count == 16 and (digits == 51 or digits == 52 or digits == 53 or digits == 54 or digits == 55):
        card = "MASTERCARD"

    # Otherwise the card number is invalid
    else:
        card = "INVALID"

    # Printing the card type
    if checkSum % 10 != 0:
        print("INVALID")

    else:
        print(card)


credit()