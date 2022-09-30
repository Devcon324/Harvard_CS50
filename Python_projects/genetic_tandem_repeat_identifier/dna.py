import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as data:
        database = csv.reader(data)
    for row in database:
        STR_sequences = row
        STR_sequences.pop(0)
        break

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as DNA_seq:
        DNAreader = csv.reader(DNA_seq)
    for row in DNAreader:
        DNA = row[0]

    # create a dictionary
    sequences = {}

    # populate dictionary with STR : count
    # start all counts at 0
    for item in STR_sequences:
        sequences[item] = 0

    # Find longest match of each STR in DNA sequence
    for str in sequences:
        longest_match()

    # Check database for matching profiles
    # open the csv as a reference dictionary to compare with STR counts
    with open(sys.argv[1], "r") as ref_file:
        reference = csv.DictReader(ref_file)

        # each row is a person
        # look at each person
        for person in reference:
            match = 0
            # now look at each STR repeat count
            # start with first STR
            for STR in sequences:
                # see if the STR repeat count == Person STR value
                # sequence[AGATC] == int(person[AGATC])
                # sequence[AATG]  == int(person[AATG])
                # sequence[TATC]  == int(person[TATC])
                if sequences[STR] == int(person[STR]):
                    match += 1
            # if the num_of_matches = how many STR'st here are
            if match == len(sequences):
                print(person['name'])
                exit()
        # if there is no satisfactionm in match == len(sequences)
        #for each person in the for loop, then there is no match
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
