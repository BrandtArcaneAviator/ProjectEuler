/*
Program to examine lexicographic permutations of
a given set of digits.  For example, for the digits
0, 1, and 2, these permutations are ordered like so:
	012  021  102  120  201  210
The goal of this program is to find the millionth
lexicographic permutation (i.e. the millionth value
in a series ordered like the above) of the digits
0, 1, 2, 3, 4, 5, 6, 7, 8, 9.

Note that lexicographic order prioritizes minimum
value by digit placement.  That is, the first position
in the first of the series should have the lowest digit
value (0 above), followed by the next smallest digit (1),
etc.  After this, the next permutation increases to the
next smallest overall value with the same first digit 
(i.e. note 012 goes to 021, 102 to 201, and 201 to 210)
until all permutations where that digit is kept constant is
found.  Note the smallest value we can make out of the
above digits is 0123456789, then next smallest is
0123456798, etc., until, presumably, 0987654321 (the largest
possible permutation where 0 is still the first digit.

To implement this form of permutation, we need at least two
layers of steps:
	1) Permutations of the first digit (on basis of
	   minimized digit value).
		2) Permutations based on overall minimized value, 
		   keeping the first digit the same for all 
		   permutations of this layer.
Since we are only swapping digits for both types of
permutations, we can use find() and swap() algorithmic 
functions operating on a vector of integer digits.  Notably,
the 2nd inner set of permutations are based on a simple
inequality (e.g. 012 < 021 < 102, s.t. we know within a
given permutation of 1), we choose the next value, b, in the
series by the inequality a < b < c, where a is the previous
value and c represents other permutations of 2)).
Since we only care about the Nth (millionth) permutation,
we don't need necessarily need to record permutations
beyond it, BUT we do need to consider other permutations
of 2) when deciding the next value in the sequence
(i.e. we must compare, e.g. for digits 0,1,2,3, and 0-th
1) permutation the values 0123, 0132, 0213, 0231, 0312, 
and 0321 across each other and arrange them appropriately).
This "sorting" is accomplished automatically using the
permutation functions below.

Also, this program utilizes stringstream input of all
digits.  That is, a user enters the digits as a string
(e.g. "0123456789") which is then converted into the
corresponding vector we can use for permutations.

I also want to point out all the permutation iteration
could've been done by std::next_permutation, which
lexicographically and iteratively orders such permutations.
It may also remove the need for giant permutation vectors
that are currently used.  It was instead done this way
to examine how to code the lexicographical order.
*/

#include "Problem24_FunctionLibrary.h" // For the function library of this problem.

int main()
{
	/*
	Get user input of string of digits:
	*/
	std::cout << "Enter all the digits for the lexicographic permutations: ";
	std::string digitStr{};
	std::cin >> digitStr;
	/* DEBUG: check the string:
	std::cout << "You entered: " << digitStr << ".\n"; 
	*/

	/* 
	Also get user input for nth permutation: 
	*/
	std::cout << "Enter which permutation you want to find (e.g. 1 = first): ";
	unsigned int nthPerm{};
	std::cin >> nthPerm;


	/*
	Allocate the digits to a manipulatable vector and sort the digits:
	*/
	std::vector<int> startPermutation{extractDigitstoVector(digitStr)};
	/* DEBUG: Show that the vector has the correct series of digits:
	std::cout << "Vector is now: " << printcurrentDigits(startPermutation).str() << ".\n";
	*/

	/*
	currentPermutation is now at the very first permutation with 0 in the
	first position.  We now need to implement the rest of the permutations 
	using the npermutations functions above:
	*/
	std::vector<std::vector<int>> permutationsVector{ permutations(startPermutation, {}) };

	/* DEBUG: check for these permutations: 
	for (std::vector<int>& a : permutationsVector)
	{
		std::cout << printcurrentDigits(a).str() << "      ";
	}
	std::cout << '\n';
	*/


	/*
	Now, permutationsVector has all the permutations up to the nth value in
	lexicographic order, meaning the last std::vector<int> in it is
	the permutation we are looking for:
	*/
	std::cout << "The " << nthPerm << "-th permutation of the digits "
		<< printcurrentDigits(startPermutation).str() << " is "
		<< printcurrentDigits(permutationsVector.at( nthPerm - 1 )).str() << ".\n";


	return 0;
}