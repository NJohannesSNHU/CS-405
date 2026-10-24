// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>


int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	// TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
	//  even though it is a constant and the compiler buffer overflow checks are on.
	//  You need to modify this method to prevent buffer overflow without changing the account_number
	//  variable, and its position in the declaration. It must always be directly before the variable used for input.
	//  You must notify the user if they entered too much data.

    // The account number must remain unchanged and directly before the input buffer.
    const std::string account_number = "CharlieBrown42";

    // The buffer can hold 19 characters plus the null terminator.
    char user_input[20];

    std::cout << "Enter a value: ";

    // Limit input to 19 characters so there is always room for the null terminator.
    // This prevents the user's input from writing beyond the end of the buffer.
    std::cin.width(sizeof(user_input));

    std::cin >> user_input;

    // If the input was longer than the buffer, the remaining characters are
    // still in the input stream. Notify the user that their input was too long.
    if (std::cin.peek() != '\n' && std::cin.peek() != EOF)
    {
        std::cout << "Warning: You entered too much data. "
            << "Only the first 19 characters were accepted." << std::endl;

        // Clear the remaining characters from the input stream.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
