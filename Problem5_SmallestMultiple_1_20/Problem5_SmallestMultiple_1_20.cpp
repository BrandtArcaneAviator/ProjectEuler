// Program to find the smallest number which is
// evenly divisible (i.e. with no remainder, modulus = 0)
// by all integers between 1 and 20.

// As a note, 2520 is the smallest number divisble by all
// numbers from 1 to 10 with no remainders.

// To implement this, we need to individually check, for all
// integers between 1 and 20 (lets call this variable n):
	// Number % n = 0 (is evenly divisible, 
	//                and is thus a multiple of n).
// If any of the n values fail this test, then we can move
// on to the next number to test. Note that 1 will always
// work for any number here, so we can ignore that case.

// Thus, we need a for loop over n from 2 to 20 for a given 
// number (the counter of an outer loop) that checks this
// condition for all n, and should only break the outer loop
// when a number that satisfies all these conditions is found.
// Note the outer loop can start at 20 (as no numbers before
// this will satisfy the last condition) and increase from
// there until a satisfactory number is identified.

#include <cstdint>
#include <iostream>

using largeint_t = int_fast32_t;

int main()
{
	// Request the limits of common dividends:
	std::cout << "Enter the lower (integer) limit for the number "
		<< "range which the smallest multiple is divisible by: ";
	largeint_t counterN_min{};
	std::cin >> counterN_min;
	std::cout << "Enter the upper (integer) limit for the number "
		<< "range which the smallest multiple is divisible by: ";
	largeint_t counterN_max{};
	std::cin >> counterN_max;

	largeint_t counterN_range{ counterN_max - counterN_min + 1 };

	largeint_t smallestMultiple{};
	largeint_t numDivisible{ 0 };
	bool isSmallestMult{ false };

	// Outer loop for smallest multiple test numbers:
	for (largeint_t counter1{ counterN_max }; counter1 < 999999999; ++counter1)
	{
		// Inner Loop for checking divisibility by n:
		for (largeint_t counterN{ counterN_min }; counterN <= counterN_max; ++counterN)
		{
			// If counter1 isn't divisible by any n,
			// break the inner loop and move to next
			// counter1.
			if ((counter1 % counterN) != 0)
			{
				numDivisible = 0;
				break;
			}

			// If counter1 is divisible by n,
			// note this in numDivisible.
			numDivisible += 1;
		}

		// If numDivisible = # of n in range, then we've found
		// the number, so break the loop.
		if (numDivisible == counterN_range)
		{
			smallestMultiple = counter1;
			isSmallestMult = true;
			break;
		}
		// Just in case, we reset numDivisible
		// before next loop:
		numDivisible = 0;
	}

	// If we find a smallest multiple (boolean true):
	if (isSmallestMult)
	{
		std::cout << "The smallest positive integer "
			<< "that is evenly divisible by all the "
			<< "numbers from 1 to 20 is: "
			<< smallestMultiple << ".\n";
	}
	else
	{
		std::cout << "Error: No smallest common multiple "
			<< "for all integers from 1 to 20 found.";
	}


	return 0;
}