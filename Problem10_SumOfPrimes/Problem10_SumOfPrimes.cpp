/*
Program to find the sum of all prime integers below
two million (what I'll call maxN = N here).

Obviously, to do so, we need to be able to identify
all prime numbers below maxN.  This can be
implemented by a Sieve of Eratosthenes algorithm, like 
in other problems involving finding prime numbers.

The way this sieve works is by creating a list (a int 
vector called vec, e.g.) of consecutive integers 
(2,3...N), identifying the first prime number (i.e. p = 2), 
and then removing all multiples of p from vec.  This 
process repeats for the next integer that has not yet 
been removed (note this by force must be a prime each 
time, since all non-primes have been sieved out).  This 
continues for each new prime until we reach p^2 > N, since by
that point all remaining numbers in the list will be
prime.  The p^2 > N condition is not immediately obvious;
but note the code would have addressed all multiples of this
p value up to this point (i.e. p*1 through p*(p-1) would've
been addressed before we considered this p because of all
previous primes being addressed first).  Lastly, note I
exclude p = 1 from this list!

An important additional note: all even numbers beyond 2
cannot be prime!  Therefore, it's unnecessary to consider
even numbers past 2 when looking for prime numbers.  A
similiar, if more complicated, idea can be applied for p = 3,
such that we can exclude consideration of all multiples of both
2 and 3 by expliciting excluding these elements, which notably
can be identified by the loops:
	for(int it{4}; it <= maxN; it += 2)
	and
	for(int it{6}; it <= maxN; it += 3).
Note these for loops start at the next multiple past 2 or 3.
We can take a similar logic for all primes past 2 by using:
	for (int i{3}; i * i < maxN ; i += 2)
	{
		for (int j{3}; j * i < maxN; j += 2)
		{
		}
	{

However, let's be clear about optimization of this algorithm:
we are then storing integers up to 2,000,000 (requiring larger
integers classes, specifically int_fast32_t works well with
its maximum integer being 2,147,483,646, noting int_fast16_t
can only go up to 32,767) in up to 2,000,000 elements of a
vector.  This is an extreme amount of memory usage for such
purposes, s.t. it is far more efficient to instead use a
vector of booleans where 0 -> false = non-prime, 1 -> true = prime.  
To accurately represent a prime list this way, however, we should
instead use the position in the vector as the actual value of
the prime.  For consistency, that means the list actually
needs to start at 0 (recall vector positions go 0,1,2,3,...etc.)
where we take 0 and 1 not to be prime, obviously.  We can then
start iterating the sieve with 2 as above (note we mean position
2 is true, i.e. prime, and then all multiples of 2 in the list
must be set to false), and the same for multiples of 3.

AFTER we address all non-primes (if we are simply summing over the
values in the list, these need to be set to zero or as we'll see,
false for a boolean vector) or specifically if we ignore the multiples
of such primes in the list (i.e. we sum within this for loop using it
as the position in the list vector), we can then perform the sum.
If we specifically ignore the multiples of 2 and 3, e.g., we get the
for loop over which we can sum here that checks for prime values, and
we use the boolean vector described above, then the sum is:
	for(int a{5}; a <= maxN; a += inc, inc = 6 - inc)
	{
		if(primes.at(a) == true)  //checks if prime:
		{
			sum += a;
		}
	}
where inc is initialized to 2, and thus inc swaps between 2 and 4
repeatedly to skip all multiples of 2 and 3 innately.  Note we
must include the if statement to catch other primes (e.g. 5 would
be obviously added here, but its not immediately obvious that 19
would be, or that multiples of 5 such as 35 would be ignored here).

Also note that for the final sum variable, we actually need
to use an even larger integer (int_fast64_t) since the answer has
more digits than int_fast32_t can provide.
*/


#include <cstdint>
#include <iostream>
#include <vector>


using lint_t = int_fast32_t;


/* Function to generate a boolean vector of primes below
a given maximum value (maxN). Uses the sieve method
detailed above: */
std::vector<bool> generatePrimeList(const lint_t& maxN)
{
	std::vector<bool> primes((maxN + 1), true); // calls vec constructor here.
	primes.at(0) = false; // Set zero to false (non-prime);
	primes.at(1) = false; // Set one to false (non-prime);


	/* Now sieve out non-primes, starting with all multiples
	of 2: */
	for (lint_t a{ 4 }; a <= maxN; a += 2)
	{
		primes.at(a) = false;
	}
	/* Now for all other non-primes; including multiples of 3.
	Note the conditions p*p > maxN is included here: */
	for (lint_t i{ 3 }; i * i < maxN; i += 2)
	{
		for (lint_t j{ 3 }; j * i < maxN; j += 2)
		{
			primes.at(j * i) = false;
		}
	}


	return primes;
}


int main()
{
	/* DEBUG: Checking max_size() of a std::vector<lint_t>,
	which needs to be AT LEAST 2 million elements large;
	returns 1,073,741,823 so we can use int_fast32_t for
	our purposes here.  Note if the max_size() of a vector
	is below maxN here*/
	/*std::vector<lint_t> testvec{};
	std::cout << testvec.max_size();*/


	/* Ask for the max number below which to
	find primes for this list: */
	std::cout << "Enter the maximum integer below which to sum prime values: ";
	lint_t maxN{};
	std::cin >> maxN;


	/* Initialize a boolean vector whose positions represents
	the list of integers for the sieve algorithm: */
	std::vector<bool> primeBoolVec{ generatePrimeList(maxN) };


	/* Initialize the sum variable and sum over all primes
	(position values of all true booleans in primes): */
	int_fast64_t finalSum{ 2 + 3 }; 
	// Note we include the first two terms in sum here.

	/* Note we know beforehand that all even positions
	beyond 2 and all multiples of 3 will return false,
	so we can utilize a for loop that skips these (e.g. see
	problem 7's solution): */
	lint_t inc{ 2 }; // increment variable for for loop below.
	for (lint_t it{5}; it <= maxN; it += inc, inc = 6 - inc)
	{
		/* If prime, add to sum: */
		if (primeBoolVec.at(it) == true)
		{
			finalSum += it;
		}
	}


	/* Now return the final sum to the user: */
	std::cout << "The sum of all primes below " << maxN
		<< " yields: " << finalSum << ".\n";


	return 0;
}