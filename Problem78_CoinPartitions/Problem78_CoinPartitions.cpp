/*
Program to find the smallest number of n coins that
can be sorted p(n) different ways into separate piles
where p(n) is divisible by one million (10^6).

For example, n = 5 coins can be separated in 7 ways
(note in this we do not discern any one specific coin):
	OOOOO
	OOOO O
	OOO OO
	OOO O O
	OO OO O
	OO O O O
	O O O O O
where the spaces here indicate a separation of piles.
Thus p(5) = 7.

Note from this example we can determine a few things.
Firstly, we can always have one pile of all n coins,
so p(n) >= 1 for all n.  Similarly, we can always have
all coins in separate piles (assuming we have more than
one), so for n >= 2, p(n) >= 2 (and thus p(1) = 1 is
fixed).  Since these two options will always be the
case regardless of n, we can ignore these two 
configurations when trying to determine p(n). Therefore,
we only need to care about configurations where we have
more than one pile, but less piles than the number of
coins (2 <= # piles < n).

Furthermore, note we ignore duplicates of a given
configuration.  That is, for example:
	OOO OO = OO OOO  or, e.g. (3,2) = (2,3)
are identical in this framework.  We must take care
then not to overcount by including duplicate cases.

With that in mind, note that there are also configurations
(if we use the notation (i,j,k,..) representing the
number of coins in each unique pile) like (n-1, 1),
(n-2, 2), etc. up to approximately (n/2, n/2) for even
n and one offset for odd n (e.g. for n = 5 above, this
is the (3,2) case).  However, as noted above, ANY 
configuration past (n/2, n/2) (or its odd equivalent)
will be a duplicate case (e.g., (2,3)) and should
not be counted for p(n).  This is approximately n - n/2
unique configurations, but note we need to be careful
for odd n here.

While we could keep going for all different types of
cases, I'll note that what we are describing herein
is known as integer partitions, i.e. the # of ways
we can write n as a sum of integers. From above for
n = 5:
	5 = 5
	5 = 4 + 1
	5 = 3 + 2
	5 = 3 + 1 + 1
	5 = 2 + 2 + 1
	5 = 2 + 1 + 1 + 1
	5 = 1 + 1 + 1 + 1 + 1
Again, notice this excludes order duplicates like
5 = 1 + 4, i.e. order-dependent compositions do not
guarantee unique partitions.  Note these are
represented as coins (Os) above in what is called
a Ferrers diagram.  With this in mind, we can
look into literature to identify p(n) as the
partition function, which has the generating
equation:
	Sigma_(n=0)^(inf) p(n) * q^n 
		= Pi_(j=1)^(inf) Sigma_(i=0)^(inf) q^(i*j)
		= Pi_(k=1)^(inf) (1 - q^k)^-1
If we expand this, we obtain:
	p(n) = p(n-1) + p(n-2) - p(n-5) - p(n-7)
		   + p(n - 12) + p(n-15) - p(n - 22)
		   + ...
Recall from above that this means p(0) = 1,
p(1) should be 1, and p(n) = 0 for n < 0.  Note
furthermore there is a repeating pattern of signs
on the elements in the sum (+,+,-,-,+,+,-,-, etc.).
The value of the subtracting nuymbers in the arguemnets
is notably a sequence of pentagonal numbers of alternating
signs. Thus, note also that this can be represented 
by the series of positive integers m=1,2,3,... such that:
	k = { m/2 + 1   if k = 0 mod 2
	    { -m/2 - 1  else
where notably the division m/2 is an integer division.
Then, from this k we calculate those values using the
pentagonal number formula:
	f(k) = k * (3*k - 1) / 2
Note this yields the expected sequence:
	1, 2, 5, 7, 12, 15, 22, ...
where, e.g., the 1 and 2 values come from:
	m = 1 using k = -m/2 - 1 -> k=-1 -> -(-3-1)/2 = 2
	m = 2 using k = +m/2 + 1 -> k=2 -> 2*(2*3 - 1)/2 -> 5
	m = 3 using k = +m/2 + 1 -> k=2 -> 2*(2*3 - 1)/2 -> 5

Also note that p(n) can become quite large for large n,
so we may run into the issue of size for integer variables.
To avoid the need for a large integer class (e.g. multiprecision
variables from boost), and noting we only need a p(n) value
that is divisible by 10^6, we technically only need to store
the last 7 digits of each number (which can be done by
using modulo (%) 10^6 before we store a given p(n) number.
*/


#include <iostream>
#include <vector>


using lint_t = int_fast16_t;


int main()
{
	/* Initialize a vector of p(n)
	values (note position zero is
	n = 0 giving p(0) = 1 here): */
	std::vector<lint_t> p{};
	p.push_back(1);


	/* Initialize variables for loops: */
	lint_t n{ 1 };
	lint_t sign{ 1 };
	lint_t k{ 1 };
	lint_t m{ 0 };
	lint_t penta{ 1 };


	/* i.e. until we find our answer: */
	while (true)
	{
		/* Reset m, penta, and initialize
		next p(n) element in vector: */
		m = 0;
		penta = 1;
		p.push_back(0);


		/* Note this loop runs for all terms
		in the expansion of a given p(n) that
		are non-zero (recall n < 0 gives p(n) = 0): */
		while (penta <= n)
		{
			/* sign yields the pattern 
			+,+,-,-,+,+,-,-,... Note sign
			starts with i = 0.*/
			sign = ((m % 4 > 1) ? -1 : 1);
			
			/* Using the pattern for the
			partition function p(n) above.
			Note this loop runs this statement 
			until p(n) is fully calculated: */
			p.at(n) += sign * p.at(n - penta);

			/* Since we don't care about large values,
			only if modulo 10^6 yields 0, we use: */
			p.at(n) %= 1000000;

			/* Now set up next penta value using the
			m values noted above to set k to get next
			pentagonal number: */
			m++;
			k = (m % 2 == 0 ? m / 2 + 1 : -(m / 2 + 1));
			penta = k * (3 * k - 1) / 2;
		}
	

		/* If statement identifying the first n
		whose p(n) % 10^6 == 9.  Note for the
		sake of avoiding large numbers this was done
		within the while loop above. */
		if (p.at(n) == 0)
		{
			/* Used to exit loop when divisible
			value is found. */
			break;
		}

		n++;
	}


	/* Now report the current value that broke the loop: */
	std::cout << "The smallest number of coins whose number of unique paritions is "
		<< "divislble by 10^6 was found to be: n = " << n << ".\n";


	return 0;
}