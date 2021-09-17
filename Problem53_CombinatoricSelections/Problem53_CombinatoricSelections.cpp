/*
Program to determine how many, not necessarily distinct,
values of the combinatoric of n and r, where r <= n and
1 <= n <= 100, that are greater than one million.

Firstly, I'll note a combinatoric is referring to the
number of ways that a range of numbers can be selected
from a range.  For example, selecting three from five
considers the range 1,2,3,4,5, from which we can find:
	123, 124, 125, 134, 135, 145, 234, 235, 245, 345
i.e. we've identified 10 separate ways of selecting
three from five.

In combinatorics, this is represented by the notation:
	(n = n! / ( r! * (n - r)! )
	r)
Here, we'll denote this notation as binomCoef(n,r) for
simplicity, since this corresponds to the binomial
coefficient.  Note the factorials here, e.g.:
	n! = n * (n - 1) * (n - 2) * (n - 3) *... * 2 * 1
The notable exception to this factorial equation 
is 0! = 1.

Note further, then, that there are some cancellations 
involved in binomCoef(n,r).  To see this, note that:
	n! = n * (n - 1) * (n - 2) * (n - 3) *... * 2 * 1
	r! = r * (r - 1) * (r - 2) * (r - 3) *... * 2 * 1
Recall that r <= n.  Then, for example, if we take 
n = 10 and r = 9:
	n!/r! = (10*9*8*7*6*5*4*3*2*1) / (9*8*7*6*5*4*3*2*1) = 10
It can then be seen from this that for a given n and 
r that the only terms that survive are those from n 
which are greater than r. Here, only 10 survives, but if 
n = 10 and r = 1, we'd effectively retain all of n!. 
Therefore, generally:
	n!/r! = n * (n - 1) * (n - 2) * (n - 3) *... * (r + 1)

Note for this problem, having a function which calculates 
factorials will be helpful.  However, if we use brute
force methodology here, we'd be calling this function
many, many times.  Instead, we can generate a list of
factorial values in a vector so we can just read these
values from memory.  Note each element in this vector
has the property n! = (n-1)! * n, which we use when
setting up this vector.

Now, notice that since this is a binomial coefficient
we could instead examine its associated Pascal's triangle 
by arranging the values (n 0), (n 1), (n 2), ... (n n)
in successive rows for n = 0,1,2,3,...maxN.  Note
that these values satisfy the recurrence relation:
	binomCoef(n,k) = binomCoef(n - 1, k) + binomCoef(n - 1, k - 1)
What this effectively means is that Pascal's triangle
can be represented by n (row number) and r (placement 
in the row) in a vector of sub-vectors with increasing
lengths (n).  However, notably, Pascal's triangle
is symmetric so we only ever need to calculate half of it
when constructing it. That is, for even n, r=1 to r=n/2
will match r=n/2 to r=n in reverse order, i.e. r=1
corresponds to the same value at r=n/2; for odd n,
r=1 to the element left of center (r=n/2 -1 but note
n/2 is not an integer value) correlates in reverse 
to element right of center (r=n/2 +1) to r=n, where 
the center element is unaffected.  Such a triangle
for 1 <= n <= 5 looks like:
			1
		   1 1
		  1 2 1
		 1 3 3 1
		1 4 5 4 1

Notably, a method of solving this problem using Pascal's
triangle and not brute force checking of factorials
entails:
	i) Constructing Pascal's triangle for 1 <= n <= 100,
	as above.

	ii) Inside Pascal's triangle, wheever we find an
	element on the left side of the triangle greater 
	than one million, we know that there are several
	elements after that which, by the symmetry of the
	triangle, are also greater than one million as
	the values increase going towards the center then
	decrease going away from the center.  Note if
	we find such a value at r, then all positions
	between r and n-r will satisfy this property.
	Therefore, there are (n - r) - r + 1 entries
	in that row greater than one million.

	iii) Then, to make use of ii), we can search
	Pascal's triangle until we find an n and r
	that yields this.  Note we were told in the
	problem statement that the first such value is
	n = 23, r = 10, so we can start at n = 23
	initially.  Then we search each subsequent row
	for values > 10^6 to find the start of the next
	set of r values.  Notice that we only need to
	identify r ONCE per row, since we then immediately
	know once a valid r is found that the row contains
	(n - r) - r + 1 elements with values > 10^6.

	iv) We perform iii) for all remaining rows (n values).

In this program, we have code for both methods 
that should give the same result.  however,
the factorial method requires MASSIVE numbers
far beyond the scope that int_fast64_t can handle,
so I'd need boost multiprecision or similar libraries
to handle that part of the code.  For now, it's
included as commented out code for posterity.
*/


#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>


using lint_t = int_fast32_t;


int main()
{
	/* Ask the user for the maximum upper bound
	(i.e. maxN) to examine factorials for: */
	std::cout << "Enter the maximum upper bound for n to examine "
		<< "combinatoric selections for: ";
	lint_t maxN{};
	std::cin >> maxN;

	/* Needed to prevent allocation problems
		for vectors later. */
	assert(maxN > 0);


	/* Counter for the # of combinatoric
	selections whose value exceeds 10^6: */
	lint_t combinatoricCounter{ 0 };


	/* Limit/threshold across which to count
	combinatoric values: */
	lint_t combLimit{ 1000000 };


	///* Brute force method using factorials: */

	//	/* Initialize the list of factorial values from
	//	0! to maxN!: */
	//std::vector<lint_t> factorialVec(maxN + 1);

	//factorialVec.at(0) = 1; // 0! = 1.

	//for (lint_t i{ 1 }; i <= maxN; ++i)
	//{
	//	// Taking advantage of n! = (n-1)! * n: 
	//	factorialVec.at(i) = factorialVec.at(i - 1) * i;
	//}


	//	/* Now brute force calculate n!/r! (n-r)!
	//	using the corresponding positions in factorialVec: */
	//for (lint_t nf{ 1 }; nf <= maxN; ++nf)
	//{
	//	for (lint_t rf{ 1 }; rf < nf; ++rf)
	//	{
	//		/* If binomCoef(n,r) > 10^6, count one: */
	//		if ((factorialVec.at(nf) / (factorialVec.at(rf) * factorialVec.at(nf - rf)))
	//			> combLimit)
	//		{
	//			++combinatoricCounter;
	//		}
	//	}
	//}

	//	/* Report counts back to user: */
	//std::cout << "The number of combinatoric selections for n, r that exceed 1,000,000 "
	//	<< "in the range 1<= n <= " << maxN << " was found to be "
	//	<< combinatoricCounter << " using factorial calculation.\n";


	/* Method generating the left half of
	Pascal's triangle for a chosen maxN.
	Recall from above that we do not need
	the full triangle, on the LHS to identify
	r whose value > 10^6: */

	std::vector<std::vector<lint_t>> pascalTriang{};
	std::vector<lint_t> rowN{};

		/* Reset counter from last method: */
	combinatoricCounter = 0;

		/* Set up the sub-vectors: */
	for (lint_t nit{0}; nit <= maxN; ++nit)
	{
		rowN.resize(nit + 1);
		pascalTriang.push_back(rowN); 
		pascalTriang.at(nit).at(0) = 1;
	}
		/* Now fill in the sub-vectors 
		with their values: */
	for (lint_t n{ 1 }; n <= maxN; ++n)
	{
		for (lint_t r{ 1 }; r <= static_cast<lint_t>(floor(n / 2.0)); ++r)
		{
			/* Utilizes the recursion
			relation in description: */
			pascalTriang.at(n).at(r) = pascalTriang.at(n - 1).at(r)
				+ pascalTriang.at(n - 1).at(r - 1);

			/* For even n rows, we need to account for a
			value that doesn't technically exist in the 
			half triangle, but we can do so using its symmetry: */
			if (r == static_cast<lint_t>(floor(n / 2.0)) && n % 2 == 0)
			{
				pascalTriang.at(n).at(r) += pascalTriang.at(n - 1).at(r - 1);
			}


			/* Now, as we construct the triangle,
			we look for values > 10^6 and use their
			position (n,r) to add counts to the counter: */
			if (pascalTriang.at(n).at(r) > combLimit)
			{
				combinatoricCounter += (n - (2 * r) + 1);
				
				/* Note we don't need to countinue any
				further on this row, so break the inner
				for loop here: */
				break;
			}
		}
	}


		/* Report counts back to user: */
	std::cout << "The number of combinatoric selections for n, r that exceed 1,000,000 "
		<< "in the range 1<= n <= " << maxN << " was found to be "
		<< combinatoricCounter << " using Pascal's triangle.\n";


	return 0;
}