// Exceptions.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <exception>

// Custom exception class derived from std::exception.
// This allows the exception to be caught specifically in main().
class CustomException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "A custom application exception occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    // Throw a standard C++ exception to demonstrate
    // handling an exception derived from std::exception.
    throw std::runtime_error(
        "Standard exception thrown from even more custom application logic."
    );

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    // Wrap the function call in a try block so that a standard
    // exception can be caught and handled locally.
    try
    {
        std::cout << "Running Custom Application Logic." << std::endl;

        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded."
                << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        // Display the exception type's message and continue processing.
        std::cout << "Standard exception caught in custom application logic: "
            << ex.what() << std::endl;
    }

    // Throw a custom exception so that it can be explicitly
    // caught by the handler in main().
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // Check for division by zero before performing the operation.
    // std::invalid_argument is a standard C++ exception derived
    // from std::exception.
    if (den == 0.0f)
    {
        throw std::invalid_argument("Cannot divide by zero.");
    }

    return (num / den);
}

void do_division() noexcept
{
    // Because this function is noexcept, the exception must be
    // handled inside this function instead of being allowed to
    // propagate to the caller.
    try
    {
        float numerator = 10.0f;
        float denominator = 0;

        auto result = divide(numerator, denominator);

        std::cout << "divide(" << numerator << ", " << denominator
            << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& ex)
    {
        // Catch only the exception type specifically thrown by divide().
        std::cout << "Division error: " << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // The entire application logic is wrapped in a try block.
    // Handlers are ordered from the most specific exception to
    // the most general.
    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& ex)
    {
        // Catch the custom exception explicitly before std::exception.
        std::cout << "Custom exception caught in main: "
            << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        // Catch other exceptions derived from std::exception.
        std::cout << "Standard exception caught in main: "
            << ex.what() << std::endl;
    }
    catch (...)
    {
        // Catch any unexpected exception that was not derived from
        // std::exception. This prevents an unhandled exception from
        // reaching the operating system.
        std::cout << "Unknown exception caught in main." << std::endl;
    }

    std::cout << "Program completed normally." << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu