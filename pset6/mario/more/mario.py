from cs50 import get_int
# Function that prompts user for a height between 1 and 8


def get_height():

    # Prompt user until heihgt is between 1 and 8
    while True:
        height = get_int("Height: ")

        if height >= 1 and height <= 8:
            return height


# Function that outputs a pyramid of the user's choice
def mario():
    # Prompt user for height
    height = get_height()

    # Loop as many times as height
    for i in range(1, height + 1):

        # Loop over all the columns in the pyramid
        for j in range(1, height * 2 + 3):

            # Print hashes
            if j > height - i and j != height + 1 and j != height + 2 and j <= height + 2 + i:
                print("#", end="")

            elif j == height + 1 or j == height + 2 or j <= height - i:
                print(" ", end="")

        # print a new line for a new row of the pyramid
        print()


mario()