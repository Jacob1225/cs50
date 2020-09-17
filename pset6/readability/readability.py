from cs50 import get_string
# Function that counts the number of words, letters & sentences


def count(text):

    # Declare a dictionary to be returned
    counts = dict()

    letterCount = 0
    wordCount = 1
    sentenceCount = 0

    # loop over each character of the string text
    for char in text:

        # if character is a letter increase count by 1
        if char.isalpha():
            letterCount += 1

        # if there is a space assuming a new word is starting
        elif char == ' ':
            wordCount += 1

        # if char is ! . or ? then a new sentence is starting
        elif char == '!' or char == '.' or char == '?':
            sentenceCount += 1

    # Populate the dictionary with counts
    counts['letterCount'] = letterCount
    counts['wordCount'] = wordCount
    counts['sentenceCount'] = sentenceCount

    return counts

# Function that determines the reading level of text


def readability():
    # Get input text from the user
    text = get_string("Text: ")

    # determine word, letter and sentence count
    counts = count(text)
    words = counts['wordCount']
    letters = counts['letterCount']
    sentences = counts['sentenceCount']

    l = letters / words * 100
    s = sentences / words * 100

    # Coleman-Liau index of text
    index = round(0.0588 * l - 0.296 * s - 15.8)

    # Validating the reading level
    if index >= 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {index}")


readability()