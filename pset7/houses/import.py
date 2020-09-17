from sys import argv, exit
import csv
import cs50

# Verify user has passed in proper number of args
if len(argv) != 2:
    print("Must provide one and only one file")
    exit(1)

# Open file for SQLite
db = cs50.SQL("sqlite:///students.db")

# Open file and read it if argument check was passed
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        student = []

        # Seperate the first, middle and last name of every student
        for i in row["name"].split(" "):
            student.append(i)

        student.append(row["house"])
        student.append(row["birth"])

        # Insert the student array into the students db
        # If student has a middle name
        if len(student) == 5:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       student[0], student[1], student[2], student[3], student[4])

        # If student has no middle name
        if len(student) == 4:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       student[0], student[1], student[2], student[3])