/*
Program to count the number of reduced proper fractions
of positive integers (n,d for fractino n/d) for
d <= 1,000,000.

First, note a reduced proper fraction has n < d (i.e.
fraction is less than one) and HCF(n,d) = 1 (that is,
the fraction is fully reduced, HCF = highest common
factor).  Importantly, this HCF() is identical to
the gcd() function in C++.

For example, for d <= 8, there exists a set of such
fractions:
	1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7,
	1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 
	7/8
where there are 21 elements in this set.

Note for this problem, we don't need to record the
numbers in the set, only the number of such fractions;
thus, we need only a counter and a proper conditional
if statement to identify the fraction as a reduced one.

Firstly, let's note that we don't need to search all
n and d values.  Obviously, by definition, for each d,
only n < d values are allowable.  But beyond this, any
fraction that can be reduced, i.e. where gcd(n,d) != 1,
is ignorable (a separate if statement that checks this
could be used to ignore such values).  Also note d should
start at 2 (i.e. n < dictates the first of such fractions
is 1/2).

Furthermore, let's note that a set of fractions with 
gcd(n,d) = 1 are relatively prime.  So a set of relatively
prime numerators that are smaller than d (for a given d)
are proper reduced fractions.  This can be recognized as
basically Euler's totient function (phi(n)), which counts
the positive integers up to n that are relatively prime to
n (i.e. in the range 1 <= k <= n for values with gcd(k,n) = 1).
In this context, this problem becomes the sum (represented by
Sigma):
	Sigma_(d = 2)^(1000000000) phi(d)

For any given d, then, we would apply:
	phi(d) = d * Pi_(p|d)(1 - 1/p )
where Pi is the multiplicative series counterpart to Sigma,
and p|d refers to all the prime factors of d.  Notably,
this means we need all the prime numbers up to 1000000000,
which is problematic in terms of runtime.  However, we can
reduce this using a sieve.  The idea behind a sieve is that
for a given array of numbers (in this case, the list of
denominators from 2 to 1000000000), we start at the first
prime (i.e. 2) and remove every multiple of that prime.
However, here we don't want to remove multiples, but instead
multiply them by the factor (1 - 1/p).  In doing this, we
account for all prime factors of every number.  Note that
any prime factor of d will have gcd(p,i) = 1 for all i < p.


PROGRAM LIMITATIONS NOTE:
This program notably has two non-obvious problems
in implementation.  First, we are making a VERY large
vector of values (and theorectically, one could ask for
even larger ranges, e.g., d <= 1,000,000,000) that if
we improperly choose the integer size, will not be
able to allocate the memory (causes std::length_error
or std::bad_alloc exceptions) when generating this vector.
To resolve this, we carefully consider both 
std::vector<int_fast32_t>::max_size() (maximum possible #
of elements in a vector of fast32 integers) and the upper
limit of positive values for int_fast32_t.  Here, the
normal choice of integer type (int_fast64_t) is sufficient for
d <= 1,000,000 in both ways, but for the larger example,
d <= 1,000,000,000, this will exceed the max_size() of
such a vector.  Note that a given fast integer type has
max value given by:
	(2^(N-1) ) - 1
so fast32 has 2^(31) - 1 = 2,147,483,647, far above
the d <= 1,000,000,000.  In addition:
	std::vector<int_fast32_t>::max_size() 
	-> 1,073,741,823
Which almost barely fits.  This became an issue for
int_fast64_t because its max_size() is dramatically less
() so it would work for d <= 1,000,000 but not for
d <= 1,000,000,000.  Thus, lint_t was changed to int_fast32_t
for this reason, even though its unnecessary for the problem
at hand.

Second, the counter can easily exceed the integer limit if we
aren't careful here.  This (presumably) is why we see a
std::bad_alloc exception thrown on the counter variable when
we input 1,000,000,000 for maxdLimit when we run the program,
even though it compiles just fine.  For this reason, I chose
an int_fast64_t for that variable, but even this is too small
from what I can gather for the d <= 1,000,000,000 case, so
this program still will not work for that.  It can, however,
run up to d <= 100,000,000, which is still useful.  Thus,
we'd need to implement boost integers here to uncap the value
this counter can go to were we to go much higher.  Boost, however,
will likely NOT help the other issue as the integer size requirement
increases for the high end of the range of the vector; therefore,
this is not a solution to the issue of vector::max_size().
*/

#include <cstdint>
#include <iostream>
#include <numeric>  // for std::iota, used to make range of d.
#include <vector>


using lint_t = int_fast32_t;


int main()
{
	/* Ask user for maximum upper limit for d: */
	std::cout << "Enter the maximum upper limit for denominator (d) values "
		<< "to search the range 2 <= d <= max for reduced proper fractions: ";
	lint_t maxdLimit{};
	std::cin >> maxdLimit;


	/* Initialize a counter for reduced proper fractions and
	an array containing all numbers in the range: */
	std::vector<lint_t> phiRange{};
	phiRange.resize(maxdLimit + 1);

	int_fast64_t counterRedPropFrac{ 0 }; // Must be larger than fast32!


	/* Fill the d range vector with integers from 0 to
	maxdLimit + 1, corresponds to their positions in
	the vector (i.e. phiRange.at(2) = 2): */
	std::iota(phiRange.begin(), phiRange.end(), 0);
	

	/* DEBUG: print phiRange to check it's values: */
	/*std::cout << "( ";
	for (lint_t a : phiRange)
	{
		std::cout << a << " ";
	}
	std::cout << ")\n"; */


	/* For loop for relevant d values; note that
	phiRange.at(2) == 2 initially in the if statement
	and that phiRange becomes the phi(d) function
	through the if statement sieving before we add
	any phiRange elements to the final sum: */
	for (lint_t d{2}; d <= maxdLimit; ++d)
	{
		/* Note this, in combination with the inner for loop,
		ensures that we only enact the sieving for prime factors: */
		if (phiRange.at(d) == d)
		{
			/* Note this loop only hits multiples of a given d: */
			for (lint_t j{ d }; j <= maxdLimit; j += d)
			{
				/* This sieves out non-prime factors of d by changing
				the value of those elements to the phi(d) function
				value (see equation in description of problem): */
				phiRange.at(j) = (phiRange.at(j) / d) * (d - 1);
			}
		}
		
		/* Here is where we count the prime factors using the sum
		of totient functions (again see equations above in description): */
		counterRedPropFrac += phiRange.at(d);
	}


	/* Now return the counter to the user as the
	total number of reduced proper fractions in the d range: */
	std::cout << "There are " << counterRedPropFrac
		<< " reduced proper fractions for the denominator range 2 <= d <= " << maxdLimit
		<< ".\n";

	return 0;
}