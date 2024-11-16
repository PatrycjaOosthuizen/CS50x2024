from cs50 import get_int

def main():
    height = get_height("Height: ")
    half_pyramid(height)

# Prompt user for valid input
def get_height(prompt):
    while True:
        h = get_int(prompt)

        # Valid input must be between 1 and 8 inclusive
        if h > 0 and h < 9:
            return h

# Print half pyramid
def half_pyramid(rows):
    for row in range(1, rows + 1):
        print(" " * (rows - row) + "#" * row)

if __name__ == "__main__":
    main()
