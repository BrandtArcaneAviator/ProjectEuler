/*
Program to identify the 10,001st prime number.

This is done by identifying prime numbers, which
is easiest done using a sieve of Eratosthenes
algorithm in a boolean function, and recording these
numbers in a vector. When this vector's size reaches
10,001, we can use the end iterator (i.e. vec.back(),
NOT vec.end(), which is an iterator PAST the last 
element) to call the prime number we are looking for.
*/


#include <iostream>
#include <vector>


using lint_t = int_fast64_t;


/* Boolean function used to identify prime values.
Utilizes a sieve methodology here and in main(): */
bool checkPrime(const lint_t& val, const std::vector<lint_t>& primes)
{
	for (lint_t prime : primes)
	{
		/* If a given square of a prime is > val, then val is prime.
		This one isn't obvious, but if val is less than
		the next squared prime checked here (e.g. 11
		but after 3*3 = 9 te next square is 5*5 = 25), this trips this
		if statement to note val (e.g. 11) is prime. */
		if (prime * prime > val)
		{
			return true;
		}

		/* If divisible by a prime, is not a prime: */
		if (val % prime == 0)
		{
			return false;
		}
	}

	/* If no existing primes satisfy either if statement,
	val is a new prime: */
	return true;
}


int main()
{
	/* Initialize a vector for holding prime numbers: */
	std::vector<lint_t> primeVec{ 2,3 }; // initialized with first few primes.
	lint_t inc{ 2 }; // for iteration in for loop


	/* For loop to check for primes.  Note this goes
	back and forth each iteration to a +2, +4, +2, +4...
	incrementation, specifically to check a) only odd
	values (we accounted for 1,2,3 above, all evens are
	not prime) and b) to avoid odd multiples of 3 (i.e.,
	9, 15, 21, etc.).  Also note this is more or less a
	while loop in so far as the condition remains true
	until we find 10,001 prime values, independent of i. */
	for (lint_t i{ 5 }; primeVec.size() < 10001; i += inc, inc = 6 - inc)
	{
		if (checkPrime(i, primeVec))
		{
			primeVec.push_back(i);
		}
	}


	/* Report the 10,001st element of primeVec as our
	answer: */
	std::cout << "The 10,001st prime number was found to be: "
		<< primeVec.back() << ".\n";


	return 0;
}