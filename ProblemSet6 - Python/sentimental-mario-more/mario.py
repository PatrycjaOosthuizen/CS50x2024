from cs50 import get_int

def main():
    height = get_height("Height: ")
    pyramid(height)

# Prompt user for a valid input
def get_height(prompt):
    while True:
        h = get_int(prompt)
        # Valid input must be between 1 and 8(inclusive)
        if h > 0 and h < 9:
            return h

# Print pyramid
def pyramid(rows):
    for row in range(1, rows + 1):
        # Print left pyramid
        print(" " * (rows - row) + "#" * row, end="")
        # Print gap of two spaces between pyramids
        print("  ", end="")
        # Print right pyramid, only hashes
        print("#" * row)

if __name__ == "__main__":
    main()
