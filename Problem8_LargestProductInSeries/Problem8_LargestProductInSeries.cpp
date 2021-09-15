/*
Program to find the maximum product of adjacent digits
in a large digit number (here, a given 1000 digit number),
and report the values of the digits and final product to the
user.

Firstly, I'll note that we want to find n adjacent digits
to multiply together.  Since they are adjacent, if we
represent each digit in the large number as positions in
a vector, then we are looking to find the digits in the
positions labeled by:
	i, i + 1, i + 2, i + 3, ... i + (n - 1)
where i here dictates a starting position (initially, i = 0
for the start of the vector).

Then, for each set of adjacent digits, we can calculate and
record their product (note each product can be associated back
to a given starting position i if we record this in a vector,
as position i in the product yields the product for n adjacent
digits starting at i in the large number vector).  Afterwards,
we can identify the maximum product and work backwards to
identify the specific digits for the product, and then report
those values to the user.

Do note, however, we can use a "sliding window" algorithm to
find the maximum product without necessarily needing to record
every product.  In this, we simply examine every n-long sequence
of adjacent digits, recording the product and its starting 
position (i) if it's greater than the previous maximum identified.
Effectivelly, this is like examining each set of adjacent positions
noted above in a for loop over i (from 0 to vec.end() - n).

Also, note crucially that ANY zero digit will cause the product to
become zero also, so we can naturally excluded any sequence with
a zero in it.  
*/


#include <iostream>
#include <string>
#include <vector>


using lint_t = int_fast16_t;


/* Function for parsing elements of a sub-string,
converting characters to integers, and multiplying them
together: */
lint_t parseAndMultiplySubStr(const std::string& substring)
{
	std::string substr1{ substring };
	std::vector<lint_t> vecDigits{};


	/* Convert substring to vector of digits (parsing): */
	for (char a : substr1)
	{
		vecDigits.push_back(static_cast<lint_t>(a - '0'));
	}


	/* Determine the product of digits in substring: */
	lint_t product{ 1 };
	for (lint_t b : vecDigits)
	{
		product *= b;
	}


	return product;
}


int main()
{
	/* Initialize the series as a string: */
	std::string series{
	"7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"
	};


	/* Ask for the length of the adjacent sub-string: */
	std::cout << "Enter the number of consecutive digits in the series to consider: ";
	lint_t n{};
	std::cin >> n;


	/* Initialize variable for max product, a test product,
	a starting position, and a boolean for finding zeroes: */
	lint_t maxproduct{ 1 };
	lint_t testproduct{ 1 };
	lint_t startpos{ 0 };
	bool zerofound{ false };


	/* Inside a for loop, check product for maximum after
	checking whether the substring contains a zero: */
	for (lint_t i{ 0 }; i < (series.length() - n); ++i)
	{
		/* Second for loop that checks if a zero exists 
		in substring: */
		for (lint_t j{0}; j < n; ++j)
		{
			if (series.substr(i, n).at(j) == '0')
			{
				zerofound = true;
				break;
			}
		}

		if (zerofound)
		{
			zerofound = false; // reset zerofound must be done here!
			continue; // I.e. skip checking product, cause it's zero.
		}


		/* Now check the substring's product and replace maxproduct if
		new product is greater: */
		testproduct = parseAndMultiplySubStr(series.substr(i, n));
		if (testproduct > maxproduct)
		{
			maxproduct = testproduct;
			startpos = i;
		}
	}


	/* We've now identified the substring that gives us our maximum
	product, so report this to the user: */
	std::cout << "The sequence of " << n << " consecutive digits in the 1000-digit "
		"number provided that yields the maximum product is: \n";
	for (lint_t c{ 0 }; c < n; ++c)
	{
		if (c == (n - 1))
		{
			std::cout << series.substr(startpos + c, 1) << " = ";
		}
		else
		{
			std::cout << series.substr(startpos + c, 1) << " * ";
		}
	}
	std::cout << maxproduct << ".\n";


	return 0;
}