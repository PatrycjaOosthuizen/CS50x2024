import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 3:
        print("Usage: python dna.py *.csv *.txt")  # Inform user about the expected usage
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)  # Append each row (profile) to the database list

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:  # Open the text file containing the DNA sequence to analyze
        dna_sequence = file.read()  # Read the entire content of the DNA sequence file

    # Extract STR subsequence keys from the first profile, excluding "name"
    subsequences = list(database[0].keys())[1:]

    # TODO: Find longest match of each STR in DNA sequence
    result = {}  # Initialize a dictionary to store results of longest matches for each subsequence
    for subsequence in subsequences:
        result[subsequence] = longest_match(dna_sequence, subsequence)  # Call function to find longest match for each STR

    # TODO: Check database for matching profiles
    for person in database:  # Loop over each person's profile in the database
        match = 0  # Initialize a counter for matching STRs found
        for subsequence in subsequences:  # Loop over each STR subsequence again
            if int(person[subsequence]) == result[subsequence]:  # Compare stored count with calculated count
                match += 1  # Increment match counter if they are equal
        # If all subsequences matched, print person's name and return from function
        if match == len(subsequences):
            print(person["name"])
            return
    # If no matches were found after checking all profiles, inform user
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
