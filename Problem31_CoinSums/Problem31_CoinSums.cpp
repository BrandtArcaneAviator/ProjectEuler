/*
Program to determine the number of different
ways 2 english pounds can be made using
any number of coins.  Note that the
coins in the UK currecy are have values
(in pence):
1p, 2p, 5p, 10p, 20p, 50p, 100p, 200p,
where the last two are the 1 and 2 pound
values (i.e. 100p = 1 pound).

We can use a counter for each unique way
we find, or use the length of a vector
containing unique permutations.  I'll
note that a vector which has values
corresponding to the # of each coin type
is an efficient way to recognize unique
ways to make 2 pounds from coins (e.g.
(200,0,0,0,0,0,0,0) is the permutation
made from 200 1p coins).  Thus, we
can record such permutation vectors
in another vector to note unique ways
(checking new permutations against this
vector for uniqueness, as with problems 
21,29).

To this end, it will be useful to have
a function which pulls each value from
the individual permutation vectors,
multiplies them by the appropriate coin
value, and sums the resulting pence values
and checks that the total returns 2 pounds 
(200p), since otherwise it is an invalid
permutation.

Also note the unique upper bounds for each 
coin type:
1p -> 200 = 2 pound
2p -> 100 = 2 pound
5p -> 40 = 2 pound
10p -> 20 = 2 pound
20p -> 10 = 2 pound
50p -> 4 = 2pound
100p -> 2 = 2 pound
200p -> 1 = 2 pound
Note that this means we cannot make a coin
combination where 200p is involved that
isn't just that coin by itself (1 unique
permutation, (0,0,0,0,0,0,0,1)), so
we can choose to drop this last value in
the vector by noting initially that the
unqiuness count starts at 1.

We can then run various numbers of coins
using permutations over the above ranges
to find our unique ways to count 2 pounds.

CAUTION: At current, this code runs very
slowly due to the sheer number of permutations
to check.  Finding an algorithmic way
to reduce the ranges of the for loops
or some other way to determine coin choices
for a given permutation may be necessary!!
*/

#include <algorithm> // for std::equal() algorithm.
#include <iostream>
#include <numeric> // for std::accumulate().
#include <vector>


/*
Function to pull values from a given
permutation vector.  Note we ignore
the 200p coin for the reasons above,
this is only for a 7-element vector.
*/
std::vector<int> calculatePenceVec(const std::vector<int>& permVec1)
{
	std::vector<int> penceVec{};
	penceVec.resize(7, 0);

	for (int it{ 0 }; it < permVec1.size(); ++it)
	{
		switch (it)
		{
		case 0: penceVec.at(it) = permVec1.at(it) * 1;   break;
		case 1: penceVec.at(it) = permVec1.at(it) * 2;   break;
		case 2: penceVec.at(it) = permVec1.at(it) * 5;   break;
		case 3: penceVec.at(it) = permVec1.at(it) * 10;  break;
		case 4: penceVec.at(it) = permVec1.at(it) * 20;  break;
		case 5: penceVec.at(it) = permVec1.at(it) * 50;  break;
		case 6: penceVec.at(it) = permVec1.at(it) * 100; break;
		default: break;
		}
	}

	return penceVec;
}

/* Function to check if sum of pence values
in a vector equals 200p (2 pounds): */
bool checkTwoPounds(const std::vector<int>& permVec2)
{
	std::vector<int> tempPence{ calculatePenceVec(permVec2) };

	/* If the sum returns 200, return true, else false. */
	if (std::accumulate(tempPence.begin(), tempPence.end(), 0) == 200)
		return true;
	else
		return false;
}


int main()
{
	/*
	Initialize a std::vector<std::vector<int>> to hold
	unique ways to count 200p:
	*/
	std::vector<std::vector<int>> uniqueCoinSets{};

	/* 
	Initialize a std::vector<int> for checking coin
	permutations:
	*/
	std::vector<int> currentCoins{};
	currentCoins.resize(7, 0);

	/* Initialize boolean for uniquenss: */
	bool isUniqueCoinSet{ true };

	/*
	Set up loops to check values of each coin type:
	*/
	// Loop for 1p values:
	for (int onep{ 0 }; onep <= 200; ++onep)
	{
		currentCoins.at(0) = onep;

		// Loop for 2p values:
		for (int twop{ 0 }; twop <= 100; ++twop)
		{
			currentCoins.at(1) = twop;

			// Loop for 5p values
			for (int fivep{ 0 }; fivep <= 40; ++fivep)
			{
				currentCoins.at(2) = fivep;

				// Loop for 10p values:
				for (int tenp{ 0 }; tenp <= 20; ++tenp)
				{
					currentCoins.at(3) = tenp;

					// Loop for 20p values: 
					for (int twentyp{ 0 }; twentyp <= 10; ++twentyp)
					{
						currentCoins.at(4) = twentyp;

						// Loop for 50p values:
						for (int fiftyp{ 0 }; fiftyp <= 4; ++fiftyp)
						{
							currentCoins.at(5) = fiftyp;

							// Loop for 100p values:
							for (int hundredp{ 0 }; hundredp <= 2; ++hundredp)
							{
								currentCoins.at(6) = hundredp;

								/* Now we check for 200p total and
								for uniqueness in uniqueCoinSets: */
								if (checkTwoPounds(currentCoins))
								{
									/* DEBUG: print this vector:
									std::cout << "(";
									for (int it{ 0 }; it < currentCoins.size(); ++it)
									{
										std::cout << currentCoins.at(it) << ", ";
									}
									std::cout << ")     "; */

									for (std::vector<int> c : uniqueCoinSets)
									{
										if (std::equal(c.begin(), c.end(), currentCoins.begin()))
										{
											// If not unique, goes here:
											isUniqueCoinSet = false;
										}
									}

									// If unique set is found that equals 200p:
									if (isUniqueCoinSet)
									{
										// Add to unique sets:
										uniqueCoinSets.push_back(currentCoins);
									}

									// Reset boolean:
									isUniqueCoinSet = true;
								}
							}
						}
					}
				}
			}
		}
	}

	/* Now we have all unique ways to count 200p
	with various coin combinations.  The total
	is therefore the number of sub-vectors in 
	uniqueCoinSets plus one (recall we excluded 
	the permutation with the 200p coin). */

	std::cout << "The maximum number of ways to count 2 UK pounds in terms of "
		<< " the 1p (pence), 2p, 5p, 10p, 50p, 100p, and 200p coins was found to be "
		<< (1 + uniqueCoinSets.size()) << ".\n";


	return 0;
}