// Implement a program that checks the validity of a given credit card number

// CS50 CHECK
// identifies 378282246310005 as AMEX
// :) identifies 371449635398431 as AMEX
// :) identifies 5555555555554444 as MASTERCARD
// :) identifies 5105105105105100 as MASTERCARD
// :) identifies 4111111111111111 as VISA
// :) identifies 4012888888881881 as VISA
// :) identifies 4222222222222 as VISA
// :) identifies 1234567890 as INVALID (invalid length, checksum, identifying digits)
// :) identifies 369421438430814 as INVALID (invalid identifying digits)
// :) identifies 4062901840 as INVALID (invalid length)
// :) identifies 5673598276138003 as INVALID (invalid identifying digits)
// :) identifies 4111111111111113 as INVALID (invalid checksum)
// :) identifies 4222222222223 as INVALID (invalid checksum)
// :) identifies 3400000000000620 as INVALID (AMEX identifying digits, VISA/Mastercard length)
// :) identifies 430000000000000 as INVALID (VISA identifying digits, AMEX length)

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int every_other_digit(long credit_card_number);
int multiplyAndSum(int last_digit);
int number_of_digits(long credit_card_number);
bool isValidAmex(long credit_card_number, int numberOfDigits);
bool isValidMasterCard(long credit_card_number, int numberOfDigits);
bool isValidVisa(long credit_card_number, int numberOfDigits);

int main(void)
{
    long credit_card_number = get_long("Credit Card: ");
    int sum_every_other_digit = every_other_digit(credit_card_number);
    int numberOfDigits = number_of_digits(credit_card_number);
    bool amex = isValidAmex(credit_card_number, numberOfDigits);
    bool masterCard = isValidMasterCard(credit_card_number, numberOfDigits);
    bool visa = isValidVisa(credit_card_number, numberOfDigits);
    // printf("%i\n", numberOfDigits);
    if (sum_every_other_digit % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    else if (amex == true)
    {
        printf("AMEX\n");
    }
    else if (masterCard == true)
    {
        printf("MASTERCARD\n");
    }
    else if (visa == true)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

bool isValidAmex(long credit_card_number, int numberOfDigits)
{ // Calculate the first two digits of the credit card number
    int first_two_digits = credit_card_number / pow(10, 13);
    // Check if the card is an American Express card
    if ((numberOfDigits == 15) && (first_two_digits == 34 || first_two_digits == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidMasterCard(long credit_card_number, int numberOfDigits)
{ // Calculate the first two digits of the credit card number
    int first_two_digits = credit_card_number / pow(10, 14);
    // Check if the card is a MasterCard
    if ((numberOfDigits == 16) && (first_two_digits > 50 && first_two_digits < 56))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidVisa(long credit_card_number, int numberOfDigits)
{ // Check for Visa cards with either 13 or 16 digits
    if (numberOfDigits == 13)
    {
        int first_digit = credit_card_number / pow(10, 12);
        if (first_digit == 4)
        {
            return true;
        }
    }
    else if (numberOfDigits == 16)
    {
        int first_digit = credit_card_number / pow(10, 15);
        if (first_digit == 4)
        {
            return true;
        }
    }
    return false;
}

int number_of_digits(long credit_card_number)
{
    int count = 0;                 // Initialize a counter to keep track of the number of digits.
    while (credit_card_number > 0) // Loop until the credit card number is reduced to zero.
    {
        count = count + 1; // Increment the digit count for each iteration.
        credit_card_number = credit_card_number / 10; // Remove the last digit by dividing by 10.
    }
    return count; // Return the total count of digits in the credit card number.
}

int every_other_digit(long credit_card_number)
{
    int sum = 0;              // Initialize a variable to accumulate the sum of processed digits.
    bool isTurnDigit = false; // Boolean flag to alternate between every other digit.
    while (credit_card_number > 0) // Continue processing until no digits are left.
    {
        if (isTurnDigit == true) // Check if it's time to process an alternate digit.
        {
            int last_digit = credit_card_number % 10; // Get the last digit of the current number.
            int product_digit = multiplyAndSum(last_digit);// Process this digit using another function.
            sum = sum + product_digit; // Add processed value to sum.
        }
        else
        {
            int last_digit = credit_card_number % 10; // Get the last digit again for non-alternate processing.
            sum = sum + last_digit; // Simply add this digit to sum without modification.
        }
        // oposite value
        isTurnDigit = !isTurnDigit; // Toggle the boolean flag for alternating behavior.
        credit_card_number = credit_card_number / 10; // Remove the last digit from the number for next iteration.
    }
    return sum; // Return total accumulated sum after processing all digits.
}
// Function to multiply the last digit by 2 and return the sum of its digits
int multiplyAndSum(int last_digit)
{ // Multiply the input last_digit by 2 and store the result in 'multiply'
    int multiply = last_digit * 2;
    // Initialize a variable 'sum' to hold the sum of the digits of 'multiply'
    int sum = 0;
    // Loop until 'multiply' becomes zero
    while (multiply > 0)
    { // Get the last digit of 'multiply' using modulus operator
        int last_digit_multiply = multiply % 10;
        // Add the last digit to 'sum'
        sum = sum + last_digit_multiply;
        // Remove the last digit from 'multiply' by performing integer division by 10
        multiply = multiply / 10;
    }
    // Return the final computed sum of digits
    return sum;
}
