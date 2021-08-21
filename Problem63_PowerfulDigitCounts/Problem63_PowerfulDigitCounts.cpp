/*
Program to determine how many n-digit integers
exist that are also an nth power.

Note, for example:
	16807 (5 digits) = 7^5
	134217728 (9 digits) = 8^9

Note that we only care about values which
have n digits that are nth powers.  Thus,
we can calculate nth powers and only consider
values which have the appropriate n digits.

Thus, we need methods to:
	1) Calculate nth powers (e.g. see problem 30's
	   function for this)
	2) Determine the number of digits in a 
	   (potentially very large) integer value.
To implement 2), we can use a function which counts
using a for loop that applies value / 10 until
that value goes below zero (i.e. its last digit).

Note there is no obvious upper bound for n-digit,
nth power values. However, consider the inequality:
	10^(d-1) <= x^n < 10^(d)
That is, for a value dictated by x^n with d digits,
we expect it to be within the lower and upper bounds
set by that digit number (i.e. 10^(d-1) and 10^(d)),
e.g. for d=3 we have bounds 100 and 1000 (as 1000 is
4 digit it has to be exlcuded in the inequality).
Notice then that since we only care for values with
d = n, this becomes the lemma L(x^n) = n, giving:
	10^(n-1) <= x^n < 10^n
Using logarithms (base 10):
	n-1 <= n * log(x) < n (the above lemma with the 1 moved over).
Note from RHS inequality we see:
	log(x) < 1, i.e. x < 10.
Thus, we just proved that the only possible bases
are single digits (i.e. 1-9)! Hence, we now know
that the loop for the base values goes from
1 <= x < 10.

But what about for the loop over n values?
Here we use the inequality:
	L(x^n) > n
Recall L(x^n) = 1 + n * log(x), so:
	n * log(x) > n -1
	log(x) > (n-1)/n = 1 - (1/n)
	log(x) + (1/n) > 1
	1/n > 1 - log(x)
	n > 1 / (1 - log(x))
	n > log(x) (in base 10/n).
Recall the max value of x is 9 (the inequality 
was 10, so):
	n > log(10) (in base 10/n)
Calculating the biggest allowed value (x=9)
yields n < 21.85.
Therefore, it is unlikely that we need consider
n beyond 21, s.t. 1 <= n <= 21 will suffice
as our range here (no 0-digit number is a thing,
and n=22, rounded up from 21.85, is unnecessary
since we only cosider whole values of n due to
the n-digit part).

ALTERNATIVE: We could also use the back relation:
	1 + n * log(x) = n
as an explicit check that x^n has n digits.

Code works as intended, but I am unsure if
there are other special cases I have neglected
in the counting.
*/

#include <cstdint>
#include <iostream>

using lint_t = int_fast64_t;

/* Function to execute power relationships: */
lint_t calculatePower(const int& base, const int& exp)
{
	lint_t result{ 1 };

	for (int i{ 1 }; i <= exp; ++i)
	{
		result *= static_cast<lint_t>(base);
	}

	return result;
}

/* Function to count the number of digits in a value: */
lint_t countNumberDigits(const lint_t& value)
{
	lint_t value1{ value };
	lint_t counter{ 0 };

	/* Note there is a special case we have to account
	 for, i.e. 0^1 yields 0 which is 1 digit. */
	if (value1 == 0)
	{
		return 1;
	}

	while (value1 > 0)
	{
		value1 = static_cast<lint_t>(floor(value1 / 10.0));
		++counter;
	}

	return counter;
}


int main()
{
	/*
	Initialize counter for how many positive 
	integers are n-digit, nth powers.
	*/
	lint_t counterNdigNPow{ 0 };

	/* 
	Implement two for loops, one for base values 
	(x above) and one for n values:
	*/

	/* Loop over bases only needs 1-9: */
	for (int x{ 0 }; x < 10; ++x)
	{
		/* Loop over n only needs to go up to n = 21: */
		for (int n{ 1 }; n <= 21; ++n)
		{
			/* If the value is n-digit, nth power: */
			if (countNumberDigits(calculatePower(x, n)) == n)
			{
				++counterNdigNPow;
			}
		}
	}

	/* Now report the counter value to user,
	i.e. the number of positive integers which
	are n-digit, nth power values:*/
	std::cout << "The total number of n-digit, n-th power positive integer values was found to be "
		<< counterNdigNPow << ".\n";

	return 0;
}