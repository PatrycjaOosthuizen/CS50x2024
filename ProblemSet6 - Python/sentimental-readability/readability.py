from cs50 import get_string

# Function to check if a character is a space, indicating the end of a word
def word_end(c):
    return c == " "

# Function to check if a character is a punctuation mark that indicates the end of a sentence
def sentence_end(c):
    return c == "." or c == "!" or c == "?"

# Function to check if a character is an alphabetic letter
def letter(c):
    return c.isalpha()

# Function to calculate the Coleman-Liau index based on letter, word, and sentence counts
def coleman_liau_index(count_letter, count_word, count_sentence):
    letter = 100 * count_letter / count_word  # Calculate the average number of letters per 100 words
    sentence = 100 * count_sentence / count_word  # Calculate the average number of sentences per 100 words
    result = (0.0588 * letter) - (0.296 * sentence) - 15.8  # Compute the Coleman-Liau index using the formula provided
    return round(result)  # Return the rounded result as an integer

# Prompting user for input text
text = get_string("Text: ")

# Initializing counters for letters, words, and sentences
count = 0
count_letter = 0
count_word = 0
count_sentence = 0

# Loop through each character in the input text to count letters, words, and sentences
for c in text:
    if word_end(c):  # Check if current character marks end of a word
        count_word += 1  # Increment word counter if it does
    elif sentence_end(c):  # Check if current character marks end of a sentence
        count_sentence += 1  # Increment sentence counter if it does
    elif letter(c):  # Check if current character is a letter
        count_letter += 1  # Increment letter counter if it is

# After loop ends, increment word counter by one to account for the last word in text
count_word += 1

# Calculate Coleman-Liau index using collected counts
index = coleman_liau_index(count_letter, count_word, count_sentence)

# Print grade level based on calculated index value
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(("Grade {}").format(index))
