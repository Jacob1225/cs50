from sys import argv, exit
import cs50

# Exit program if more than one argument provided
if len(argv) != 2:
    print("Must provide one and only one argument")
    exit(1)

# Validate if house exists
houses = ["hufflepuff", "ravenclaw", "slytherin", "gryffindor"]

if argv[1].lower() not in houses:
    print("Invalid house name")
    exit(1)

# Connect to database file

db = cs50.SQL("sqlite:///students.db")

# Query database
rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# Format results
for row in rows:

    # If student has a middle name
    if row['middle']:
        print(f"{row['first']} {row['middle']} {row['last']}, born in {row['birth']}")

    else:
        print(f"{row['first']} {row['last']}, born in {row['birth']}")

