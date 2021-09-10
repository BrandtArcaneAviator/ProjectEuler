/*
Program to identify the four non-trivial examples
of "two-digit, digit cancelling fractions" and calculate
their products' (in lowest common terms) denominator.

Firstly, note that a two-digit "digit cancelling fraction"
is one where a) the numerator and denominator have two digits
each and b) one of the digits in the numerator and one in the
denominator match (and naively, one may think we can cancel this
digit to reduce the fraction, which is incorrect generally).
Crucially, to my understanding, doing this reduction must
be mathematically true for this to be such a fraction.
For example:
	49/98 shares a 9, so naively cancelling it yields 4/8.
	49/98 = 4/8 (by noting that we can extract 12.25 from each).

There are only four non-trivial (by which we mean any fraction
with zeros, e.g. 30/50 = 3/5 is trivial) examples of such
a fraction that are less than one and contain two digits in
the numerator and in the denominator.

Therefore, we must identify these four fractions.
We also know that we need a method to identify
similar digits in the numerator and denominator; we avoid this
problem by using the algebraic analysis below.

We also need to consider that, like the fraction above, the
mathematical reduction may need to be done with double values,
and is likely best done via a greatest common denominator
identification (note that in <numeric> gcd(x,y) is
a function for this, but only for integers).  It is currently
unclear if this works as intended using only gcd(x,y).

However, lets note that we can further consider how these
fractions are set up and reduce the number of values we need to
check.  There are, notably, four cases we could encounter, for a
given set of digits 1 <= n < d <= 9 (n < d forces fraction to be
less than one) and 1 <= i <= 9 such that:
	1) (10*i + n) / (10*i + d) = n/d
	2) (10*n + i) / (10*d + i) = n/d
	3) (10*i + n) / (10*d + i) = n/d
	4) (10*n + i) / (10*i + d) = n/d
Examining 1) by multiplying the denominators out, we see that
one of the terms cancels out by substraction, leaving:
	1) --> 10*d*i + n*d = 10*n*i + n*d --> d = n
But recall we fixed n < d, so this case is impossible.

Similarly, for 2), we encounter the same problem:
	2) --> 10*n*d + d*i = 10*n*d + n*i --> d = n
For 3):
	3) --> 10*d*i + n*d = 10*n*d + n*i --> 9*n*d = 10*d*i - n*i
	   --> 9nd = 10di + (di - di) - ni --> 9nd = 9di + i*(d - n)
	   --> 9*d*(n-i) = i*(d - n)
Note that since d > n, the RHS is positive, forcing n > i on the
LHS.  If we rearrange further:
	3) --> n - i = (i/9) - (i*n/9*d)
Notice that the LHS must be >= 1 here by n > i.  However, since
i < 9 on the first term of the RHS yields something less than one
and subtraction will not make this larger than 1, this equation has
no solutions.

Therefore, ALL the solutions must come from 4):
	4) --> 10*n*d + d*i = 10*n*i + n*d --> 9nd = 10ni - di
	   --> 9nd = 10ni + (ni - ni) - di --> 9*n*(d - i) = i (n - d)
Notice in this case that n < d makes the RHS negative, which forces
d < i on the LHS, such that n < d < i must be true.  Thus, our
solutions come from:
	4) (10*n + i) / (10*i + d) = n/d, with n < d < i.
This can be easily implemented in three nested for loops for n, d, and i.
*/

#include <cstdint>
#include <iostream>
#include <numeric> // for std::gcd()


using lint_t = int_fast64_t;


int main()
{
	/*
	Initialize two variables for the numerator product and the
	denominator prodcut.  Note we can do the lowest common
	denominator reduction at the end to get our proper answer
	(effectively doing all the fraction reductions all at once).
	*/
	lint_t numerProduct{ 1 };
	lint_t denomProduct{ 1 };


	/* Using nested for loop and 4) from above, identify the
	fractions and multiply their numerators and denominators: */
	for (int i{ 1 }; i < 10; ++i)
	{
		for (int d{ 1 }; d < i; ++d)
		{
			for (int n{ 1 }; n < d; ++n)
			{
				/* Using equation 4) here; if true this is one of
				the fractions we want to identify: */
				if ((((n * 10 + i) * d) == (n * (i * 10 + d))))
				{
					numerProduct *= n;
					denomProduct *= d;
				}
			}
		}
	}


	/* Now use GCD to reduce the final fraction
	(numerProduct/denomProduct): */
	denomProduct /= std::gcd(numerProduct, denomProduct);


	/* Now report this value back to the user: */
	std::cout << "The product of all two-digit, digit-cancelling fractions "
		<< "has a denominator (in lowest common terms) of " << denomProduct
		<< ".\n";


	return 0;
}