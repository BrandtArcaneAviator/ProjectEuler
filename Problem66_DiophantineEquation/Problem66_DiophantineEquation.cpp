/*
Program to identify the value of D in the diophantine 
equations described by:
	x^2 - D * y^2 = 1
for which the maximum value of x is obtained while we
search for minimal solutions of x.  That is, in a given
range of D values (e.g. [2,3,5,6,7]), we have the equations:
	3^2 - 2 * 2^2 = 1
	2^2 - 3 * 1^2 = 1
	9^2 - 5 * 4^2 = 1   (!!!)
	5^2 - 6 * 2^2 = 1
	8^2 - 7 * 3^2 = 1
Note the maximum value of x here is 9, for D = 5, while
we consider the minimal solutions (i.e. values of x and y) 
that will satisfy the equation for the range D <= 7.

Note that in that range of D, we did not include 1 or 4.  This
is because we can assume that no solutions (i.e. of positive
integers x, y, D) have "square" D values.  Thus, this means
we must exclude any square D values for a given range of D.
To this end, we should create the range of D as a vector
where we intentionally exclude these numbers up to the maximum 
value for that range (e.g. all squares up to 7 in the previous case).  

Here, we want to identify this kind of specific D for the range
D <= 1000.  Thus, after creating the range vector for D, we
then check various values of y (starting at positive integer
1) that satisfy the Disophantine equation for a given D and record
the first x value (the minimum value of x, i.e.) which satisfies
this equation for smallest y (this is done by an if statement that
catches the first occurence).  Note that, in this way, we are solving
the Diophantine equation for x for a given D and y, only recording the
case where x returns a whole integer.  We then repeat this algorithm 
for each D value until we have the full vector of minimal x values
(that directly corresponds, element to element, x to D value).
From using max_element() from <algorithm>, we find the element
position of the maximum value of x in that range, and use it
in the D range vector to identify the D value we are looking for.

Note, for integer size considerations, we need positive integers
that can become quite large (note, e.g., that D = 1000 would
require x^2 close to 999, assuming y=1; we'd thus need, at
minimum, integer values close to and above 1000 being allowed).
For the sake of avoiding overflows, we use int_fast64_t here.

For clarity, this algorithm is:
	i) Create a vector representing the full range of D values,
	excluding square D valeus.
	Do note that to determine if D is square, we use the
	inverse equation (i.e. a sqrt()) to see if the number
	is a whole integer (i.e. in n^2, only whole integers n
	will return a n^2 = D here).  This uses the if statement
	relation sqrt(D) != floor(sqrt(D)) to ignore square values.

	ii) For each value in the D vector, identify the Disophantine
	equation it satisfies that has the minimum x for minimum y.
	This corresponds, naturally, to the first occurance of
	satisfying the equation for a y loops starting at 1.

	iii) When ii) is satisfied, record that minimal x in
	a vector, where the position of that x correponds to
	the position of the D used in the equation.

	iv) Repeat ii)-iii) for the next D value, until all
	D values in the range vector have found valid x values.

	v) Scan the x vector for the maximum value of x, and
	use the position of that x value in its vector to
	identify the associated D value.

	vi) Return this D value to the user.


	Edit:
	Since 3 for loops of substaintial size scales as N^3,
	this program runs quite slowly as described above.
	Doing some research on the Diophantine equation
	shows that this specific form in this program is
	known as Pell's equation (x^2 + D * y^2 = 1).
	According to said research, the fundamental solution
	for such an equation utilizing a solution (which 
	minimizes x) like this:
		x = h_i, y = k_i, 
	where h_i/k_i is the sequence of convergence to the 
	regular continued fraction of sqrt(D).  Notably,
	problem 64 of ProjectEuler deals with this kind of
	continued fraction. Thus, we can utilize the code
	for that problem here to calculate the continued
	fraction expansion and testing each successive
	convergent expansion until a solution is found.

	This allows us to solve for minimal x without the 
	need for the x and y loops dictated above.  Thus,
	this program will now be altered to incorporate this
	method.

*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using lint_t = int_fast64_t;


/* Boolean function that checks the Diophantine equation
for a given D, x, and y.  Returns true if the Diophantine
equation for those values is satisfied. */
bool checkDiophantineEqn(const lint_t& d1, const lint_t& x1, const lint_t& y1)
{
	if (((x1 * x1) - (d1 * (y1 * y1))) == 1)
		return true;
	else
		return false;
}


int main()
{
	/* Ask for the maximum value of D to generate a range
	of D values for: */
	std::cout << "Enter the maximum value for D in the Diophantine equations: ";
	lint_t maxD{};
	std::cin >> maxD;


	/* Construct the vector for the range of D values: */
	std::vector<lint_t> dRange{};
	
	for (lint_t a{ 1 }; a <= maxD; ++a)
	{
		/* If D is square, it's square root is a whole number.
		This statement will fail, then, for such D values, and
		therefore those values are ignored. */
		if (sqrt(static_cast<double>(a)) != floor(sqrt(static_cast<double>(a))))
		{
			dRange.push_back(a);
		}
	}


	/* Now we initialize the vector for x values 
	and set up two for loops (one for x, one for y)
	starting from 1. */
	std::vector<lint_t> minXValues{};
	bool xisFound{ false };


	for (lint_t d : dRange)
	{
		for (lint_t x{ 1 }; x <= 100000; ++x)
		{
			for (lint_t y{ 1 }; y <= 10000; ++y)
			{
				if ( checkDiophantineEqn(d, x, y) )
				{
					minXValues.push_back(x);
					xisFound = true;
				}

				if (xisFound == true)
				{
					break;
				}
			}
			
			if (xisFound == true)
			{
				break;
			}
		}
	
		/* Reset xisFound for next D value: */
		xisFound = false;
	}

	/* DEBUG: print the contents of the x and D vectors:
	for (lint_t it{0}; it < dRange.size(); ++it)
	{
		std::cout << "For D = " << dRange.at(it) << ", min x = " << minXValues.at(it) << ".\n";
	} */


	/* We now have the full x vector, so find the
	maximum value of x in that vector and record it's value
	and its position in the vector:*/
	lint_t maxXposition{ distance(minXValues.begin(), std::max_element(minXValues.begin(), minXValues.end())) };
	lint_t maxXValue{ minXValues.at(maxXposition) };
	lint_t maxXDValue{ dRange.at(maxXposition) };

	
	/* Now report the value of max x and associated D
	yielding the maximum x in that range of D: */
	std::cout << "For the range D <= " << maxD << ", the maximum value of x in the minimized "
		<< "Diophantine equations is " << maxXValue << " corresponding to D = " << maxXDValue
		<< ".\n";


	return 0;
}