from sys import argv, exit
import csv


# Function that finds a dna match


def dna():
    # Verify if two command line arguments provided
    if len(argv) != 3:
        print("Must provided two and only two arguments")
        exit(1)

    # If the two arguments provided then open csv file
    with open(argv[1], newline='') as inputfile:
        reader = list(csv.reader(inputfile))
        reader[0].remove('name')

    # Open the text file
    with open(argv[2], "r") as sequence:
        data = sequence.read()

    results = []
    # Loop over each str in the top row of
    for i in range(len(reader[0])):

        position = 0
        max = 0
        count = 0
        prev = 0

        # Loop through the whole dna sequence
        while position < len(data):
            position = data.find(reader[0][i], position)

            # If a sequence was not found break out of the loop
            if position == -1:
                break

            # If a sequence was found we need to start counting consecutive strs
            elif position != -1 and prev == 0:
                count += 1
                max = count
                prev = position

            # If a consecutive sequence is found
            elif position != -1 and prev == (position - len(reader[0][i])):
                count += 1

                if max < count:
                    max = count
                prev = position

            # If a non consecutive sequence is found
            elif position != -1 and prev != (position - len(reader[0][i])):

                # reset count
                count = 1
                prev = position

                if max < count:
                    max = count

            # Increment position by 1 at each iteration of the loop
            position += 1

        # Add the str count to the results list
        results.append(max)

    # Compare results list to the database file
    # Loop through reader
    for i in range(1, len(reader)):
        pos = 0
        # Loop through each person's dna scores
        for j in range(1, len(reader[i])):

            # If results do not match move on to next person in db
            if int(reader[i][j]) != results[pos]:
                pos += 1
                break

            # If you are at the last result in the list then you have a match
            elif pos == len(reader[i]) - 2:
                print(reader[i][0])
                exit(0)

            else:
                pos += 1

    # If you have not exited the program yet, no match has been found
    print("No Match")
    exit(1)


dna()