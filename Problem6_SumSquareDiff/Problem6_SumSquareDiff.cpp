// Program to calculate the difference between the
// sum of the squares (e.g. 1^2 + 2^2 +...) and the
// square of the sum (i.e., (1 + 2 + 3 + ...)^2) for
// natural numbers (here, from 1-100).

// To do this, we implement an object with two sum variables:
// sum2 and sumSquares.  Notably, sum2 (sum squared) will
// be kept as a normal sum until after the very end of the
// sum for loop (where the integer counter n goes from 
// 1 to 100), while sumSquares will require the counter
// to be squared when adding to it.

// We'll also include one more member variable for the 
// difference of the sums: diffSums.

#include <iostream>


class SumSquareDiffSet
{
private:
	int m_sum2{};
	int m_sumSquares{};
	int m_diffSums{};

public:
	SumSquareDiffSet() : m_sum2{ 0 }, m_sumSquares{ 0 },
		m_diffSums{ 0 }
	{
	}

	int& getSum2() { return m_sum2; }
	int& getSumSquares() { return m_sumSquares; }
	int& getDiffSums() { return m_diffSums; }

	// Function to add to (sum)^2: 
	void addToSum2(int& a) { m_sum2 += a; }

	// Function to add to sum of squares:
	void addToSumSquares(int& b) { m_sumSquares += (b * b); }

	// Function to calculate sum^2 - sumSquares:
	int& calculateDiffSums()
	{
		m_diffSums = ((m_sum2 * m_sum2) - m_sumSquares);
		return getDiffSums();
	}

	// Not used here, but to reset SumSet:
	void resetSumSet()
	{
		m_sum2 = 0;
		m_sumSquares = 0;
		m_diffSums = 0;
	}
};


int main()
{
	// Request the maximum natural number to calculate
	// the sums up to (e.g. 100):
	std::cout << "Enter the largest natural number for "
		<< "the sums: ";
	int counterMax{};
	std::cin >> counterMax;

	// Initialize the SumSet object:
	SumSquareDiffSet SumDiffSet{};

	// Now we set up the for loop over natural numbers
	// up to counterMax, and then we iterate this loop
	// with each step adding values to the two sum variables:
	for (int counter1{ 1 }; counter1 <= counterMax; ++counter1)
	{
		SumDiffSet.addToSum2(counter1);
		SumDiffSet.addToSumSquares(counter1);
	}

	// Now we calculate the difference of the sums and print
	// the result:
	std::cout << "The difference between the sum of squares "
		<< "and the square of the sum for natural numbers up to "
		<< counterMax << " is: " << SumDiffSet.calculateDiffSums()
		<< ".\n";

	return 0;
}