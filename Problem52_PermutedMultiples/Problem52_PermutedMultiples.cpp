/*
Program to find the smallest positive integer x
that has 2x, 3x, 4x, 5x, and 6x which are all
permutations of the same digits.

For this purpose, we implement a function
which extracts the digits of a given value
to a vector so that confirming they have
the same digits is easier.

Note we only care about values with the same
digits, i.e. we can drop a given x value if
2x and 3x don't have the same digits. Note 
also that we will ignore comparisons to the 
digits of x.

For these comparisons, we use a simple
algorithm of sorting the associated vectors
(such that they arrange digits in ascending
order).  If two numbers have identical,
sorted vectors, then they contain the
same digits.  Note this comparison MUST
fail if the numbers have less or more digits
than one another (further notice that the
extract function constructs vectors with
sizes dependent on this, so a comparison
using std::equal() should fail).
*/

#include <algorithm> // for sort(), equal() functions.
#include <cstdint>
#include <iostream>
#include <sstream> // for stringstreams.
#include <string>
#include <vector>

using largeint_t = int_fast64_t;

/* Function to extract digits of an int value
into a vector: */
std::vector<int> extractDigitstoVec(const largeint_t& val)
{
	std::stringstream valSS{};
	valSS << val;
	std::string valStr{};
	valSS >> valStr;

	std::vector<int> valVec{};

	for (int it{0}; it < static_cast<int>(valStr.length()); ++it)
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
	/*
	First, lets initialize a loop for x values,
	and the variables for the loops:
	*/
	largeint_t mult1{ 2 };
	largeint_t value1{ 0 };
	largeint_t value2{ 0 };
	largeint_t smallestValidx{0};
	int sameDigitcounter{ 0 };
	

	for (largeint_t x{ 1 }; x < 1000000; ++x)
	{	
		value1 = mult1 * x;
		
		/* Now we need a second loop to check multiples in: */
		for (largeint_t mult2{ 3 }; mult2 <= 6; ++mult2)
		{
			value2 = mult2 * x;

			/* Now, extract these values to vectors
			   and compare their digits: */
			if (checkSameDigits(extractDigitstoVec(value1), extractDigitstoVec(value2)))
			{						
				/* DEBUG: print when same digits are found:
				std::cout << "For x = " << x << ", 2x = " << value1 
					<< " matches " << mult2 << "x = "<< value2 
					<< " in digits.\n"; */

				/* If they have same digits, increment counter: */
				++sameDigitcounter;
			}
			else
			{
				/* Note that if we find that they don't
				have the same digits, we can ignore that x,
				so break out of this inner for loop: */
				break;
			}
		}

		/* Only true if all iterations in inner loop
			increase the counter, i.e. 3x,4x,5x,6x digits 
			all match 2x digits.  Records x and escapes loop.
			note since we search x in ascending order, this
			yields the smallest valid x we are looking for. */
		if (sameDigitcounter == 4)
		{
			smallestValidx = x;
			break;
		}

		/* Reset the conditional counter for new x:*/
		sameDigitcounter = 0;
	}

	/* If no value was found: */
	if (smallestValidx == 0)
	{
		std::cout << "No positive integer x was found that has "
			<< "2x, 3x, 4x, 5x, and 6x which contain the same digits.\n";
	}
	else /* Valid x was found: */
	{
		std::cout << "Positive integer x = " << smallestValidx
			<< " has 2x, 3x, 4x, 5x, and 6x which contain the same digits.\n";
	}

	return 0;
}