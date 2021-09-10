/*
Program to find the value of positive integer n for which
its fraction with its associated Euler's totient function (phi(n)),
i.e. n/phi(n), is maximized for the range n <= 1,000,000.

Firstly, let's discuss phi(n).  This function counts the number
of relatively prime positive integers compared to n.  Therefore,
e.g.:
	n = 2 -> 1 is relatively prime -> phi(n) = 1 -> n/phi(n) = 2
	n = 3 -? 1,2 are relatively prime -> phi(n) = 2 -> n/phi(n) = 1.5
	... 
	n = 9 -> 1,2,4,5,7,8 -> phi(n) = 6 -> n/phi(n) = 1.5
	n = 10 -> 1,3,7,9 -> phi(n) = 4 -> n/phi(n) = 2.5
	etc.
Note, by the division at the end, that n/phi(n) may not be an
integer itself, so we must use double variables for that instead.
Furthermore, note in the set of n <= 10 above, the maximized value of
n/phi(n) turns out to be for n = 6 (where n/phi(n) = 3).

To find n/phi(n), we thus first need to be able to calculate phi(n).
As in problem 72 (Counting Fractions), this is reasonably done through
the product version of phi(n):
	phi(n) = n * Pi_(p|n)(1 - 1/p) = n * Pi_(p|n) (1/p * (p - 1))
where Pi is the multiplicative series (i.e. the multiplicative 
equivalent of Sigma, which represents a sum) and p|n refers to
distinct prime integers less than n that divide n.  Notice then,
that what we are actually solving for in terms of values is:
	n/phi(n) = (n/n) * 1/( Pi_(p|n)(1 - 1/p) )
I.e., what we actually want to do here is minimize the totient
value for a given set of n values.  Notice this occurs for the
n with the most distinct, small, prime factors (i.e. the largest
number of prime divisors).  This is effectively like maximizing the
number of fractions in the denominator of the above equation. 
Ideally, then, we could simply multiply distinct primes together 
until we reach the largest number less than the limit (here, 1,000,000).  
This does, however, requires a means to generate primes to give us a 
list of primes below the maxn value.

Note to avoid memory issues, this is best done via using the positions
in a boolean vector (where notably, a true value is prime and a false
value is not) to represent said numbers.  Thus, we need a boolean vector
of size maxn + 1 (so that we include zero) that we then scan for non-primes 
and setting their values equal to false.  Also note that because this is 
a factorization of maxn in a sense, we only need to find the primes up to 
sqrt(maxn), i.e.1000 (10^3 vs. 10^6).  However, we opt to use a vector
of all primes up to maxn (even 1,000,000) simply because the vector size 
of a boolean vector won't be an issue here, and I had issues implementing
a proper means of using sqrt(maxn) as the upper bound of this vector in
terms of the last for loop (the prime multiplication part).  It may be
possible, but we avoid that complexity here.
*/


#include <cstdint>
#include <iostream>
#include <vector>


using lint_t = int_fast32_t;


int main()
{
	/* Ask user for upper bound of n: */
	std::cout << "Enter the upper bound for n values: ";
	lint_t maxn{};
	std::cin >> maxn;


	/* Initialize a boolean vector to identify primes from, and the
	variable for multiplying primes: */
	std::vector<bool> primeBoolVec((maxn + 1), true);
	primeBoolVec.at(0) = false; // .at(0) represents zero.
		// NOTE this is from 0 to maxn! i.e. primeBoolVec.at(0) represents 0.
	lint_t result{2}; // Note this is accounting for 1 * 2.


	/* Modify boolean vector to set non-primes to false.  Note
	this explicitly ignores all even values (but note 1,2 needs to
	manually included above).  Also note we can exclude factors
	greater than sqrt(maxn). */
		/* Note we must exclude even values beyond 2 entirely, so
		starting at 4 (i.e. position 4, the 5th element in vector): */
	for (lint_t a{ 4 }; a <= maxn; a += 2)
	{
		primeBoolVec.at(a) = false;
	}
		/* Now we deal with remaining (odd) values: */
	for (lint_t i{3}; i * i < maxn; i += 2)
	{
		for (lint_t j{ 3 }; j * i < maxn; j += 2)
		{
			/* At any non-prime number generated by these loops: */
			primeBoolVec.at(j * i) = false;
		}
	}


	/* DEBUG: Print the vector: */
	/* std::cout << "( ";
	for (bool a : primeBoolVec)
	{
		std::cout << a << " ";
	}
	std::cout << ")\n"; */


	/* Now we perform the multiplication until we find
	the largest number below maxn.  Note we must use an 
	external counter here for the while loop: */
	lint_t p{ 3 }; // counter for while loop.

	while (result * p <= maxn)
	{
		/* If p is a prime, multiply the result by it: */
		if (primeBoolVec.at(p) == true)
		{ 
			result *= p;
		}
		

		/* Increment counter by two since all even values 
		besides 2 will return false anyway: */
		p += 2;
	}


	/* Now return the maximum value as our result: */
	std::cout << "The n for which n/phi(n) is maximized was found to be n = "
		<< result << " for the range n <= " << maxn << ".\n";

	return 0;
}