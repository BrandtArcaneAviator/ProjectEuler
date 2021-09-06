/* 
Program to count the number of fractions in the
continued fraction expansion of sqrt(2) that
have a numerator which has more digits than the 
denominator.  

Notably, the continued fraction of sqrt(2) takes 
the form:
	sqrt(2) = 1 + 1 / ( 2 + (1 / (2 + 1 / (2 + ... 
Thus, the first 4 iterations are:
	sqrt(2) = 1 + 1/2 = 3/2 = 1.5
			= 1 + 1/(2 + 1/2) = 7/5 = 1.4
			= 1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
			= 1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

Notably, the next three expansions yield 99/77, 239/169, 
and 577/408.  The one after that (the eighth expansion)
is 1393/985, which has more digits in the numerator than
in the denominator.  Notably, this means we know the first
occurance of such a fraction (i.e. at the 8th expansion),
from which we can start counting such fractions.

To solve this problem, we need to be able to:
	a) Calculate out the i-th expansion of the
	continued fraction of sqrt(2), but specifically
	in fractional form.  This is necessary in order to
	count the digits of the numerator and the denominator.
	To this end, implementing a fraction class may be
	helpful.  Notably, a non-member function that calulates
	the sqrt(2) expansion could then be implemented.
	Also note that this may be best implemented by a recursive
	method (i.e. recurse the expansion i times).

	b) We need to be able to count the numer of digits
	in an integer value (taken from the fraction, either
	the numerator or denominator).  We can do this using
	the code from problem ?? where we needed to count digits
	in a similar manner.  From this, we can then use a boolean
	function that compares the number of digits in the numerator
	to that in the denominator.  For envelopment purposes, we'll
	keep this boolean function and the associated function for
	extracting digits separate from the fraction class itself.

Notice from the numerators and denominators in the sequence above
that we can derive the following relationships:
	n_(k+1) = n_k + 2*d_k
	d_(k+1) = n_k + d_k
where, here, n is the numerator and d is the denominator. Note we
can also substitute the first eqn into the second to give:
	n_(k+1) = n_k + 2*d_k
	d_(k+1) = n_(k+1) - d_k
which eliminates one of the variables.  Thus, we can use
the numerators and denominators of past fractions to calculate
the next fraction.  This eliminates the need for more and more
complicated recursive solutions of the overall continued fraction
itself.

The algorithm for this problem would then be:
	i) Initialize counter for fractions with more digits
	in their numerator than denominator, and a temporary
	fraction class object to contain the fraction of an
	i-th convergence of sqrt(2).

	ii) In a for loop for i values (starting with the known i=8th
	expansion), calculate the (fractional) value of a given i-th 
	expansion of sqrt(2) and record it in the temporary fraction 
	class object.  This is done using a function which takes the 
	previous fractional continued fraction expansion that iterates 
	to the next expansion using the logic presented above.

	iii) Now we compare the number of digits in the numerator to
	that in the denominator using a boolean function (which needs
	to internally extract the digits from int values).  This function
	will return true when the number of digits in the numerator exceeds
	that in the denominator.  Thus, we use an if statement with
	this function as its condition, such that when the function returns
	true, we increase the counter inside the if statement.

	iv) Repeat ii)-iii) for all i-th expansions up to a maximum
	i value (here, requested as 1000).

	v) After all expansions have been checked, return the counter
	to the user as the number of fractions with higher digit numerators.

***CAUTION!***
Note there are overflow concerns in this problem! We may need to use
even larger integer classes than int_fast64_t.  At current, the
problem's algorithm works as intended, but I am not convinced that
overflows do not occur in the numerators and denominators for very 
late iterations (e.g., i = 1000th expansion likely has very large
numerator and denominator).
*/

#include <cstdint>
#include <iostream>

using lint_t = int_fast64_t;


/* Simple fraction class: */
class Fraction
{
private:
	lint_t m_numer{};
	lint_t m_denom{};

public:
	Fraction() : m_numer{0}, m_denom{1}
	{
	}

	Fraction(lint_t numer, lint_t denom) : m_numer{ numer }, m_denom{ denom }
	{
	}

	lint_t& getNumer() { return m_numer; }
	lint_t& getDenom() { return m_denom; }

	void setNumer(const lint_t& numer1) { m_numer = numer1; }
	void setDenom(const lint_t& denom1) { m_denom = denom1; }
};


/* Function to calculate the next fractional iteration of the 
expansion in the continued fraction.  Since we only deal with 
sqrt(2), here, this is built solely for sqrt(2) expansions.
Note this may not work for other sqrt(A) because the iteration
equations may not be the same as these. */
Fraction calculateNextExpanSqrt2(Fraction& fracIn)
{
	Fraction tempFrac{};

	tempFrac.setNumer( fracIn.getNumer() + 2 * fracIn.getDenom() );
	tempFrac.setDenom( tempFrac.getNumer() - fracIn.getDenom() );

	return tempFrac;
}


int main()
{
	/* Initialize counter and temporary fraction object.
	Note we initialize this object to the 8th i value: */
	Fraction frac_ithExp{1393, 985}; // i = 8th expansion.
	lint_t counterNumDigVsDenomDig{0};


	/* Ask user for maximum i-th value for iterations: */
	std::cout << "Enter the maximum number of expansions for sqrt(2): ";
	lint_t maxi{};
	std::cin >> maxi;


	/* For all iterations of i in range, record the number 
	of fractions which have more digits in numerator than 
	denominator using the counter: */
	for (lint_t i{ 8 }; i < maxi; ++i)
	{
		/* Counts the number of digits of a given fraction 
		class object.Note this funciton utilizes the reduction
		via log10 of a large number to output the # of digits 
		(effectively floors the remainder of 
		log10(B * 10 ^ n) = n * log10(B), e.g., leaving only 
		the # of digits(n).  Then compares the digits of
		numerator against those in denominator, yielding true
		if digitnum > digitdenom and increasing the counter when
		true is reached. */
		if (static_cast<lint_t>(log10(frac_ithExp.getNumer())) > static_cast<lint_t>(log10(frac_ithExp.getDenom())))
		{
			++counterNumDigVsDenomDig;
		}

		frac_ithExp = calculateNextExpanSqrt2(frac_ithExp);
	}


	/* Now return the value of the counter to the user: */
	std::cout << "The number of fractions produced by continued fractional expansions "
		<< "of sqrt(2) that have numerators with more digits than their denominators was "
		<< "found to be: " << counterNumDigVsDenomDig << ".\n";


	return 0;
}