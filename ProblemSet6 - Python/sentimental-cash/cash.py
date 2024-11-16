from cs50 import get_float

def main():
    change = get_change_owed("Change owed: ")
    cents = dollars_to_cents(change)

    # Prompt the user for change owed, in cents
    print(cents_to_coins(cents))

# Prompt user for an amount of change
def get_change_owed(prompt):
    # Start an infinite loop to repeatedly ask for input until a valid value is received
    while True:
        # Call the function get_float with the provided prompt to get user input
        n = get_float(prompt)
        # Check if the returned value n is greater than 0
        if n > 0:
            # If n is valid (greater than 0), exit the loop
            break
    # Return the valid positive float value n
    return n

# Convert dollars to cents
def dollars_to_cents(amount):
    c = round(amount * 100)
    return c

# Convert an amount in cents into the number of coins (quarters, dimes, nickels, and pennies).
def cents_to_coins(cents):
    # Calculate how many quarters are in the total cents.
    quarters = cents // 25
    # Calculate how many dimes are left after removing quarters.
    dimes = (cents % 25) // 10
    # Calculate how many nickels are left after removing quarters and dimes.
    nickels = ((cents % 25) % 10) // 5
    # Calculate how many pennies are left after removing quarters, dimes, and nickels.
    pennies = ((cents % 25) % 10) % 5
    # Return the total number of coins as a sum of all types.
    return quarters + dimes + nickels + pennies

if __name__ == "__main__":
    main()
