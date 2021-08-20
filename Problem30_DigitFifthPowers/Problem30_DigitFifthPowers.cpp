/*
Program to calculate the sum of all numbers
that can be written as the sum of the fifth
powers of their digits.

Note this means we must identify all integer
values that satisfy the corresponding relation,
e.g. for fourth powers we have:
	1634 = 1^4 + 6^4 + 3^4 + 4^4
	8208 = 8^4 + 2^4 + 0^4 + 8^4
	9474 = 9^4 + 4^4 + 7^4 + 4^4
Thus: 1634 + 8208 + 9474 = 19316.

Therefore, for this purpose, we need a function
which extracts digits to a vector (like in problem
52, which we pull this from).  From this vector,
we then need to calculate the sum of its digit's
fifth powers and check that this equals the value
itself.  We implement this as a boolean function
which takes the value and the vector extracted value
as inputs (i.e. check(val, extractDigits(val)) ).

Note also that as in the problem description for 4th
powers, we must ignore values with only 1 digit (e.g.,
1^4) since they cannot be a sum.
*/

#include <iostream>
#include <sstream> // for stringstream class.
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

	for (int it{ 0 }; it < static_cast<int>(valStr.length()); ++it)
	{
		/* Requires an implict type-cast from char to int,
		hence the - '0'. */
		valVec.push_back(valStr[it] - '0');
	}

	return valVec;
}

/* Function to execute power relationships: */
largeint_t calculateDigitPower(const int& digit, const int& exp)
{
	largeint_t result{ 1 };

	for (int i{ 1 }; i <= exp; ++i)
	{
		result *= static_cast<largeint_t>(digit);
	}
	
	return result;
}

/* Function to check if the sum of a value's 
   digits' fifth powers is equal to the value.
   Returns true if the value satisfies this
   equality, false otherwise.  Note when called
   in main() this should have implicit call to 
   extractDigits() in its second parameter.*/
bool checkDigitFifthPowers(const largeint_t& value)
{
	largeint_t sumDigitFifthPower{ 0 };
	std::vector<int> valueDigits{ extractDigitstoVec(value) };

	for (int digit : valueDigits)
	{
		sumDigitFifthPower += calculateDigitPower(digit, 5);
	}

	if (sumDigitFifthPower == value)
		return true;
	else
		return false;
}


int main()
{
	/*
	Initialize a total sum variable:
	*/
	largeint_t sumTotal{};

	/* DEBUG: Vector to record value of the total sum: */
	std::vector<largeint_t> sumComponents{};
	
	/*
	For loop for finding numbers who are the sum of
	their digits' fifth powers. Note we must start 
	with two digit values (i.e. at 10), since 1-digit
	values aren't sums.

	Also note the upper bound of this loop is not obvious.
	However, since these are single digits, we can note a
	reasonable range is:
		10^(d-1) <= d * 9^5 < 10^(d)
	where d represents the number of digits.  Applying
	logarithms (base 10) to this inequality yeilds:
		(d-1)log(10) <= log(d) + 5log(9) < d log(10)
		(d-1) <= log(d) + 5log(9) < d
		d-log(d) <= 5log(9) + 1 < d - log(d) + 1
	Note 5log(9) + 1 = 5.77, approximately:
		d - log(d) <= 5.77 < d - log(d) + 1
	Since we expect d - log(d) to be somewhat close to d,
	we can plug d=5 into the logarithms:
		d <= 6.47 < d + 1
	Thus, we might expect the max upper bound to be 7 digits
	at the most (i.e. 10000000 = 10^7, which covers up to
	999999).  Also note that 7 * 9^5 = 413343, which covers
	almost half that range (note this is the maximum SUM
	value for digits' fifth powers, and thus also caps the
	value itself).
	*/
	for (largeint_t value1{10}; value1 <= 413343; ++value1)
	{
		if (checkDigitFifthPowers(value1))
		{
			sumTotal += value1;
			sumComponents.push_back(value1);
		}
	}

	/* Report the value of the sum to the user: */
	std::cout << "The sum of all numbers that can be written as "
		<< "the sum of the fifth powers of their digits yields "
		<< sumTotal << ".\n";

	/* DEBUG: Also report the components of the sum.*/
	std::cout << "The components of this sum are: ";
	for (int i{ 0 }; i < sumComponents.size(); ++i)
	{
		if (i != (sumComponents.size() - 1))
			std::cout << sumComponents.at(i) << " + ";
		else
			std::cout << sumComponents.at(i);
	}
	std::cout << " = " << sumTotal << ".\n";

	return 0;
}