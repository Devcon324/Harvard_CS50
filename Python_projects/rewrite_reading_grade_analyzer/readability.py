# get user input
text = input("Text: ")

# declare tracking variables
# words always starts at 1 to account for last word
# assumes user inputs atleast 1 word and not empty
letters = sentences = 0
words = 1

# point at each letter in text
for pointer in text:
    # if the pointer is an alphanumeric, increment "letters"
    if pointer.isalpha():
        letters += 1
    # if the pointer can be found in list (space), increment "words"
    if pointer in [' ']:
        words += 1
    # if the pointer can be found in list (./?/!), increment "sentences"
    if pointer in ['.', '?', '!']:
        sentences += 1

# L = the average number of letters per 100 words in the text
# S = the average number of sentences per 100 words in the text.
L = letters / words * 100
S = sentences / words * 100
index = 0.0588 * L - 0.296 * S - 15.8
grade = int(round(index))

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")