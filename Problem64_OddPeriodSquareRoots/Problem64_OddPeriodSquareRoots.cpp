/*
Program to calculate the periodic square root of
a continued fraction, used ultimately to count the
number of continued fractions in the range N <= 10000
which have an odd period.

To clarify, all square roots are periodic when written
as a continued fraction, taking the appearance:
	sqrt(N) = a_0 + (1 / a_1 + (1 / a_2 + (1/ a_3 + ....
For example, sqrt(23) can be expanded as: 
	sqrt(23) = 4 + sqrt(23) - 4
			 = 4 + 1/ (1/ (sqrt(23) - 4))
			 = 4 + 1/ (1 + (sqrt(23) - 3)/7)
			 ...
It can be shown that the sequence this produces in the
a_i values can be represented by the form:
	sqrt(23) = [4; (1,3,1,8)] = [a_0; (a_1,a_2,_a3,a_4)]
where a_0 is separated from the repeating sequence in
parantheses (i.e. thus, a_1 = a_5, a_2 = a_6 and so on),
which repeats indefinently.  Therefore, the "periodic"
part of this is the repeating sequence, and its periodicity
is determined by the number of values that repeat (here,
we have a period = 4).

Notably, here we specifically care about counting the
continued fractions which have an odd period (i.e. this
period = 1,3,5,...).  Therefore, we need:
	a) The ability to solve a continued fraction to
	various convergences (i.e. out to the i-th a_i value).
	This is done using a function that takes the N value
	and the maximum i value as parameters.
	
	b) The ability to recognize the period of a continued
	fraction.  This could be done by noting the a_i values
	in a vector and checking that vector's periodicity by
	checking for repeated elements.  Note that, in the end,
	we don't care so much about the repeated sequence itself,
	so we only need to return a boolean (i.e. a yes) when
	we find that the period is odd in length.  This, again,
	should be done in a function.

The algorithm to solve this problem would then be:
	i) Initialize a counter variable for odd period
	continued fractions, and an empty vector to save a_i
	values temporarily.

	ii) In a for loop for n values up to a maximum value
	(here, the goal is maxN = 10000), we calculate the
	continued fraction out to a reasonable maximum i-th
	convegence and save it in the a_i vector noted in i).
	This is done by the function noted in a).

	iii) Within the for loop for n, we then check whether
	or not the periodicity of this a_i vector is odd or
	even, and we increment the counter variable only
	for odd period results.  This is done by an if statement
	and the boolean function noted in b).

	iv) We repeat ii)-iii) for all n values.  After the for
	loop finishes, we return to the user the number of
	counted continued fractions with odd periods.

I will note that this problem builds off the solution for 
Problem 57, which deals with a simplier case of continued
fractions but specifically for sqrt(2) expansion.
However, this solution therein is not really translatable
to her as the iteration equations are different.
*/

#include <cstdint>
#include <iostream>
#include <vector>

using lint_t = int_fast64_t;


/* Function to solve a continued fraction expansion
out to the i-th convergence. Returns a vector of
a_i values that solve the fraction for a given n. */
std::vector<lint_t> calculateithContFract(const lint_t& n, const lint_t& i)
{
	std::vector<lint_t> aitempVec{};

	for (lint_t it{ 0 }; it < i; ++it)
	{
		;
	}

	return aitempVec;
}


/* Boolean function to check if a given set of a_i values
has odd periodicity.  Returns true if the periodicity is
an odd value (i.e. if period % 2 != 0), false otherwise. */
bool checkAiOddPeriod(const std::vector<lint_t>& aiVec)
{
	if (true)
		return true;
	else
		return false;
}


int main()
{
	/*
	d
	*/


	return 0;
}