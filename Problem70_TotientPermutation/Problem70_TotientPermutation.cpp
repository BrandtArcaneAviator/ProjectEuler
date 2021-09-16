/*
Program to find the value of n in the range 1 < n < 10^7,
for which its totient function, phi(n), is a permutation 
of n and for which the ratio n/phi(n) produces a minimum.

As a reminder, the totient function represents the number 
of positive numbers (integers) less than or equal to n 
which are relatively prime to n (e.g., 1,2,4,5,7,8 are 
all < 9 and relatively prime to it, s.t. phi(9) = 6).
Note in this context the value 1 is relatively prime to
all positive numbers (even phi(1) = 1, then).

Also note, given the permutation idea, that we can't
consider any 1 digit n (i.e. the actual lower bound
is 9) because permutations of 1-digit numbers are not
possible.  With 2 or more digits, we can permute the
digits, though.

Also note, from problem 69 we know that phi(n) has a form:
	phi(n) = n * Pi_(p|n)(1 - 1/p) = n * Pi_(p|n) (1/p * (p - 1))
where Pi is the multiplicative series (i.e. the multiplicative 
equivalent of Sigma, which represents a sum) and p|n refers to
distinct prime integers less than n that divide n.  From this,
the ratio n/phi(n) is then:
	n/phi(n) = (n/n) * 1/( Pi_(p|n)(1 - 1/p) )
Thus, to achieve a minimum value for n/phi(n), we actually want
to maximize the denominator here ( Pi_(p|n) (1 - 1/p) ).  Notice
then that (1 - 1/p) for any positive prime integer p is less than
one.  Therefore, the maximum denominator here is the one for n
values that have the LEAST number of large, distinct prime divisors 
(the opposite from what problem 69 was asking for), such that we 
minimize the number and value of any fractions in this denominator.

However, we should note we only need to consider n for which its
associated phi(n) yields a permutation of n's digits.  Notably, this
also means that n and phi(n) must have the same number of digits.
Therefore, we don't need to check permutations for such cases.

Note the more obvious choice then would be to examine large prime
number as close to the upper bound as possible (i.e. close to but 
below 10^7), then.  However, note that since any prime must end 
in 1, 3, 7, or 9, phi(n) = n - 1 (the notable upper bound on phi(n)
itself) only changes the last digit and therefore this will not 
yield a permutation of n.

The second best thing we could examine, then, is two large prime
divisors of n that are as close to sqrt(n) as possible. Thus, in
this instance, we'd want distinct prime factors of n close to
sqrt(10^7) which approximately equals 3162.  Therefore, it makes
sense to scan prime numbers between 2000 and 5000, for example,
for these divisors. Notably, this is not a trivial definition
for calculating any n (e.g. 9 has less than two distinct prime 
divisors), however, but it will give us the minimized ratio
for the given range of n here.

Notice then, that in this instance, phi(n)
becomes a two-term approximation:
	phi(n) = n * (1 - 1/p_1) * (1 - 1/p_2)
		   = (p_1 * p_2) * (1 - 1/p_1) * (1 - 1/p_2)
		   = (p_1 - 1) * (p_2 - 1)
where we utilize multiplication by p1/p1 and p2/p2, alongside
p1 * p2 = n to reduce the equation.  Note this is a version
of the power form of the totient equation:
	phi(n) = Pi(p|n) (p_i^(k_1 - 1) * (p_i - 1))
where we specifically only use two p values, with both powers
equal to 1 (s.t. the power terms disappear).

As a result, the algorithm to solve this problem should entail:
	1) Utiliznig the prime list generator from problem 10,
	initialize a boolean vector of primes out to the max n (10^7).

	2) For each n between 9 < n < 10^7, starting from large n and
	counting down, calculate phi(n) using the two term approximation 
	suggested above.  If phi(n) is not a permutation of the digits 
	of n, ignore that n.  Note this is best done backwards, i.e.
	use for loops through p_1 and p_2 to examine n values in
	the range.  Recall that the minimized n/phi(n) ratio should
	occur for prime divisors in the range 2000-5000 from above.

	3) If phi(n) is a permutation of n's digits, then check the
	number of distinct prime divisors of that n and record both
	n and this number in separate vectors.

	4) Repeat 2)-3) until all n that satisfy the permutation
	requirement are found.

	5) Identify the n which has the minimum number of distinct
	prime divisors (i.e. this minimizes n/phi(n), see above),
	and report it back to the user.

To implement said algorithm, I'll use:
	i) The prime list generator from problem 10 (included as
	a function) that returns a boolean vector with position
	values corresponding to integers starting from 0, with
	false = 0 -> non-prime and true = 1 -> prime in the vector
	itself.  Thus, prime integers are set up to return true,
	non-primes return false in this vector.

	ii) The calculation of phi(n) using the product eqn above
	which must be done in main().  We need phi(n) explicitly
	here to check its digits against n for permutations.

	iii) The ability to identify permutations of two numbers.
	We include this as another function with code taken from
	problem 62(which deals with permutations in this way).  Note
	this function should reject any values of phi(n) that have
	more or less digits than n.  Do note this function works by
	sorting the digits of both numbers (lexicographically s.t. we
	get the first permutation of said digits), and returns true
	only if both resultant sorted digit vectors are the same 
	(this proves that they are permutations without needing to
	check every possible permutation).  It also utilizes the 
	function to extract digits from an int value used in several 
	other ProjectEuler problems.

Edit: I've seen some other solutions to this problem yielding
different values than what I get here, but I cannot for the life
of me identify how they are correct over this code.  Be aware,
then, this code may be wrong in a way I cannot for the life of
me identify.
*/


#include <algorithm> // for sort() and equal()
#include <cstdint>
#include <iostream>
#include <sstream> // for stringstream classes.
#include <string>
#include <vector>


using lint_t = int_fast64_t; 
// Needed as n could have as many as 8 digits


/* Function to generate a boolean vector of primes below
a given maximum value (maxN). Uses the sieve method
detailed in problem 10: */
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


/* Function to extract digits of an int value
into a vector: */
std::vector<int> extractDigitstoVec(const lint_t& val)
{
	std::stringstream valSS{};
	valSS << val;
	std::string valStr{};
	valSS >> valStr;

	std::vector<int> valVec{};

	for (int it{ 0 }; it < static_cast<int>(valStr.length()); ++it)
	{
		/* Requires an implict type-cast from char to int,
		hence the - '0'. */
		valVec.push_back(valStr[it] - '0');
	}

	return valVec;
}


/* Function to determine whether two vector contain
the same digits by first sorting them and then using
std::equal(): */
bool checkSameDigits(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
	std::vector<int> temp1{ vec1 };
	std::vector<int> temp2{ vec2 };

	/* Sort the copied vectors: */
	sort(temp1.begin(), temp1.end());
	sort(temp2.begin(), temp2.end());

	/* If these vectors are identical, they contain
	the same digits, so return true: */
	if (std::equal(temp1.begin(), temp1.end(), temp2.begin()))
		return true;
	else
		return false;
}


int main()
{
	/* DEBUG: checking sqrt(n) values: */
	/*std::cout << sqrt(13) << '\n';
	std::cout << static_cast<lint_t>(round(sqrt(13))) << '\n'; */


	/* The maximum upper bound for n here is 10^7: */
	lint_t maxN{10000000};


	/* Generate list of primes: */
	std::vector<bool> primes{ generatePrimeList(maxN) };


	/* Now find the minimized totient that is also
	a permutation of n: */
	lint_t totientN{ 1 };
	lint_t finaltotientN{ 1 };
	lint_t currentN{ 1 };
	lint_t finalN{ 1 };
	bool largestPrimesPermuteFound{ false };
	long double nphin{0.0};
	long double finalnphin{ 0.0 };

	/* Note these two loops count up to find the best option. */
		/* Identify two largest distinct prime divisors around sqrt(maxN): */
	for (lint_t primeit1{ 2001 }; primeit1 <= 3500; primeit1 += 2)
	{
		for (lint_t primeit2{ primeit1 + 2 }; primeit2 <= 3500; primeit2 += 2)
		{
			/* Excludes non-primes and non-disinct pairs of primes: */
			if (primes.at(primeit1) == true && primes.at(primeit2) == true
				&& primeit1 != primeit2)
			{
				/* Also ignore any N above maxN: */
				if ((primeit1 * primeit2) < maxN)
				{
					/* CurrentN, totientN, and nphin are replaced for the
					currently largest prime divisors: */
					currentN = primeit1 * primeit2;
					totientN = (primeit1 - 1) * (primeit2 - 1);
					nphin = (static_cast<long double>(currentN) / totientN);

					/* Now check that n and phi(n) are permutations: */
					if (checkSameDigits(extractDigitstoVec(currentN), extractDigitstoVec(totientN))
						&& nphin < std::numeric_limits<long double>::infinity())
					{
						/* Only executes if we both get a permutation
						and minimize n/phi(n) and saves the proper final
						answer.  Note this will execute for each such
						case until we find the highest one (i.e. one
						with two largest distinct prime divisors). */
						finalN = currentN;
						finaltotientN = totientN;
						finalnphin = nphin;
						largestPrimesPermuteFound = true;
					}
				}
			}
		}
	}


	/* Note if largestPrimePermuteFound is false by
	this point, we didn't find what we're looking for,
	so return error to user: */
	if (!largestPrimesPermuteFound)
	{
		std::cout << "Error: no valid phi(n) permutation with minimized n/phi(n) was found.\n";
	}
	else
	{
		/* Otherwise, report the n, phi(n), and 
		n/phi(n) back to user: */
		std::cout << "n = " << finalN << " was foud to have phi(n) = "
			<< finaltotientN << " which is a permutation of n that yields the "
			<< "minimized n/phi(n) = " << finalnphin << " for the range 1 < n < 10^7.\n";
	}


	return 0;
}