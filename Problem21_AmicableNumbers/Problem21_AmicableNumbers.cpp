/*
Program to evaluate the sum of all amicable numbers
under 10000 (i.e. 10^4).

To define an amicable number, consider d(n) as the
sum of proper divisors of a given number n
(i.e. d(n) is the sum of numbers less than n
that divide evenly into n, e.g. n % a = 0).
If:
	1) d(a) = b,
	2) d(b) = a,
	3) a != b,
Then a and b are an amicable pair and each of
a and b are called amicable numbers.

For example, proper divisors of the following #s are:
	220: 1,2,4,5,10,11,20,22,44,55,110
		--> d(220) = 284.
	284: 1,2,4,71,142
		--> d(284) = 220.
So 220 and 284 are amicable numbers.

To solve this problem, we need an algorithm to
solve for amicable pairs of numbers (note duplicate
a and b values are a concern, e.g. double counting
(220,284) and (284,220)).  Firstly, we need to be
able to evaluate d(n) for a given n up to the
maximum value (here, 10000); to this end, we'll
need to be able to find the even divisors of a given
n value.  This can be done with the modulus and a
for loop whose bounds go up to a given a, b.
Note we don't need to record the divisors themselves,
only their sums (i.e. we want two vectors, one of n
values, one of their d(n) sums with correlating 
positions), so using a function to calculate d(n)
is worthwhile.

Once we know n to d(n) correlations, we can identify
amicable pairs by searching the vectors for corresponding
values.  Note here that this means we first examine the
corresponding d(a) for a given a (i.e. in the vectors,
this corresponds to the same position in each vector).
Then we search the n vector for the value d(a) (i.e.
we are finding b now), find its corresponding d(b)
value (again same position as b is in the n-vector), and
check it's value against a.  Note we must ensure in
this process that we ignore a = b values.

Notably, we really only want to save amicable pairs in
the long run, since we need those for the final sum.
To this end, we could instead hard code at least one of the
conditions above; we can do so by searching explicitly
for amicable pairs.  That is, for a given d(a) = b, we
should calculate both d(a) = b and immediately thereafter
d(b).  Then, if d(b) = a AND a != b, we note both a and b
as amicable and add them to the vector which we'll sum
over at the end.  We then need to check for amicable
pairs in this way (again, note the risk of duplicates,
which could be alievated by checking whether the value(s)
already exist) for all n up to 10000.
*/

#include <cstdint> // For large integer types.
#include <iostream>
#include <numeric> // for std::accumulate().
#include <vector>

using largeint_t = int_fast64_t;

/* Function to calculate d(n) sums: */
largeint_t calculateDnSum(const largeint_t& n)
{
	largeint_t dnSumTemp{ 0 };

	/* Identify all even divisors of n: */
	for (largeint_t i{ 1 }; i < n; ++i)
	{
		/* If even divisor, add to sum. */
		if (n % i == 0)
			dnSumTemp += i;
	}

	return dnSumTemp;
}

/* Function to check for Amicable pairs.  Note
that to call this properly in main(), use
checkAmicablePair( a, calculateDnSum(a) ). */
bool checkAmicablePair(const largeint_t& a, const largeint_t& b)
{
	/* We can check all 3 conditions here: */
	if (calculateDnSum(a) == b && calculateDnSum(b) == a && a != b)
		return true;
	else
		return false;
}


int main()
{
	/*
	Ask for the maximum number (max n) to sum amicable
	numbers up to:
	*/
	std::cout << "Enter the maximum number under which to sum amicable numbers: ";
	largeint_t maxN{};
	std::cin >> maxN;

	/* 
	Initialize the vector to hold amicable numbers
	and a boolean to check if pair already exists
	in this vector:
	*/
	std::vector<largeint_t> amicableNums{};
	bool isNotInAmicNums{ true };

	/*
	Now we need to check for amicable pairs across the
	range of 1 to maxN.  Note we must deal with duplicates
	by checking against the current values in amicableNums,
	NOT adding values if they match an element in it.
	*/
	for (largeint_t it{ 1 }; it < maxN; ++it)
	{
		// Check if it, d(it) is a n amicable pair:
		if (checkAmicablePair(it, calculateDnSum(it)))
		{
			/* If amicable pair is found, check its not
			in amicableNums first: */
			for (largeint_t c : amicableNums)
			{
				if ( c == it || c == calculateDnSum(it) )
				{
					// If it is in amicableNums, don't add it:
					isNotInAmicNums = false;
				}
			}

			/* Adds amicable pair if they are not already
			in the vector: */
			if (isNotInAmicNums)
			{
				amicableNums.push_back( it );
				amicableNums.push_back( calculateDnSum(it) );
			}
		}

		/* Reset boolean for next it value: */
		isNotInAmicNums = true;
	}

	/*
	We now have the full vector of amicable nums up
	to maxN, so we sum over all the values using
	std::acummulate() to get the final sum:
	*/
	largeint_t amicableNumSum{ std::accumulate(amicableNums.begin(), amicableNums.end(), 0 ) };

	std::cout << "The sum of all amicable numbers below " << maxN
		<< " is " << amicableNumSum << ".\n";


	return 0;
}