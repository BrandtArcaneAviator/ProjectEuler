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
	p(n) = p(n-1) + p(k-2) - p(k-5) - p(k-7)
		   + p(k - 12) + p(k-15) - p(k - 22)
		   + ...
Recall from above that this means p(0) = 1,
p(1) should be 1, and p(n) = 0 for n < 0.  Note
furthermore there is a repeating pattern of signs
on the elements in the sum (+,+,-,-,+,+,-,-, etc.).


*/


#include <iostream>


using lint_t = int_fast16_t;


int main()
{
	/* d */



	return 0;
}