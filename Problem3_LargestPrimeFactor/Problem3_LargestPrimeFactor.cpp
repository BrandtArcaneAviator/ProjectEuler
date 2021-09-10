/*
Program to find the largest prime factor of the number
600,851,475,143.

Notably, this means we need to be able to identify prime
numbers, then use num % prime == 0 as an identifier of
that prime being a factor.  Also note that by factorization,
we can divide the number each time by the factor we just
recorded.  Take note that we can do this MULTIPLE times
for each prime factor if its some multiple of that
prime (i.e. num divisible by 9 means divide by 3 twice).

Also note, as a simplification of the code here (for
efficiency), we don't need to check even numbers (this
number is odd, so 2 isn't a factor either) and we only
need to check primes up to sqrt(num).
*/


#include <iostream>
#include <vector>


/* Note this is needed because num has 12 digits: */
using lint_t = int_fast64_t;


int main()
{
	/* Initialize the fixed number to find prime factors
	for, and a vector to hold its prime factors.
	Note we exclude 1 here since it is not a proper factor. */
	lint_t num{ 600851475143 };
	lint_t primeFactor{}; 


	/* For loop to check prime values: */
	for (primeFactor = 3; num > 1; primeFactor += 2)
	{
		/* NOTE this is a while loop and not an if
		statement because by doing it this way, we
		immediately factorize out any higher prime
		multiple (e.g. if the number were divisible
		by 9 we'd divide by 3 twice in this loop to
		remove those factors). */
		while (num % primeFactor == 0)
		{
			num /= primeFactor;
		}
	}


	/* Note once we get here, we have reached the largest
	prime factor (which reduced num below 1 via division),
	so repor this value back to user: */
	std::cout << "The largest prime factor of the number "
		<< 600851475143 << " was found to be " << primeFactor << ".\n";


	return 0;
}