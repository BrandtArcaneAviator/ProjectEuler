/* 
Program to caclulate the sum of the digits in a
number created as a power of 2.  for example,
2^15 = 32768 and this sum is thus:
3 + 2 + 7 + 6 + 8 = 26.
Using this program, we want to find the sum of digits
in the number 2^1000.

To do this, we need three things:
    1) The ability to calculate powers of 2 into large
       integer numbers.
    2) The ability to sum over digits in this number.
    3) The ability to store extremely large integers.
Notably, 2) is easily solved by using % 10 and division
by 10 inside a while loop (a copy of the power of 2 number
may be preferable if we want to preserve the result of 1)).
In regards to 1), we utilize the pow() function from 
ctgmath. 

As for 3), even int_least64_t will not be large enough,
so we instead need to dynamically allocate memory in
order to store the number itself.  This can be done
using a string to store the number.  We can then turn
the value of this string into the digit vector
needed for 2) using an iterator.
*/

// #include <ctgmath> // Needed for pow() function, but depricated
#include <iostream>
#include <sstream> // For stringstream.

/*
NOTE!!!! Should really utilize these alongside <sstring>
(i.e. stringstream) input of the power function
to get the number.  We can then use the while loop
to pull the values from the string "vector" and avoid
creating another vector for digits, and just sum over
these.  At current, this code doesn't work.
*/
// #include <boost/multiprecision/cpp_int.hpp>
// #include <boost/multiprecision.integer.hpp>


int main()
{
    /*
    Ask for an input power of two:
    */
    std::cout << "Enter the power of two to sum the digits of: ";
    int powertwo{};
    std::cin >> powertwo;

    /*
    Initialize the number variable and calculate the
    power of two.
    Note: this NEEDS to be done using multiprecision
    and conversion to a string via stringstream, as
    conversion errors will occur for pretty much any
    integral data type given how many digits these numbers
    can have.
    */
    /*
    unsigned long long int numberPowTwo{ static_cast<unsigned long long>(pow(2,powertwo)) };
    std::cout << "Power of two: 2^" << powertwo << " = "
        << numberPowTwo << '\n';
    */


    /*
    Initialize a sum variable and construct an 
    std::vector for the digits: 
    */
    /*
    int sumDigitsPowTwo{ 0 };
    std::vector<int> numberDigits{};
    */


    // For each digit in the string:
    /*
    while (numberPowTwo > 0)
    {
        numberDigits.push_back(static_cast<int>( numberPowTwo % 10 ));
        numberPowTwo = (static_cast<unsigned long long>(floor((numberPowTwo) / static_cast<unsigned long long>(10))));
    }
    */

    /*
    Now we sum the individual digits (elements) in 
    the vector using sumDigitsPowTwo:
    */
    /*
    for (int i : numberDigits)
    {
        sumDigitsPowTwo += i;
    }
    */

    /*
    Now we print the sum of the digits to the user:
    */
    /*
    std::cout << "For 2^" << powertwo << ", the sum of "
        << "its digits yields " << sumDigitsPowTwo << ".\n";
    */

    return 0;
}