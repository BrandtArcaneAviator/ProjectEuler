// Program to find the sum of all numbers below 1000 (i.e.
// what I'll call nMax here) that are multiples of 3 or 5.  
// A for loop is used to sweep over the multiples of 3 and 5.
// Note we can intentionally ignore numbers which aren't 
// multiples, so we instead use the form 3*n and 5*n for 
// a range of n up to the maximum multiple of the smallest 
// factor that is below or equal to 1000.

// To that end, note that 5 x 200 = 1000, and 3 x 333= 999,
// such that we know that the n for multiples of 3 has the
// range 1 <_ n_3 <_ 333, and the range for multiples of 5 is
// 1 <_ n_5 <_ 200.  To generalize this to any given maximum
// number below or at which we sum multiples of 3 or 5,
// we define n3Max and n5Max as:
	// i) n3Max = static_cast<int>(floor(static_cast<double>(nMax) / 3))
	// ii) n5Max = static_cast<int>(floor(static_cast<double>(nMax) / 5))
// where we use the floor function from '' to find the
// closest whole multiple (i.e. non-fractional number) to 
// nMax.

// We then define two sub-sums: one for multiples of 3 (sum3)
// and one for multiples of 5 (sum5), which utilize for
// loops over n_3 and n_5 respectively (in the ranges defined
// above).  These sums are implemented using two sum variables
// as member variables of a class MultipleSumSet object, which
// also holds member variables for n3Max and n5Max, as well
// as a final sum variable, totalSum.

#include <cmath>
#include <iostream>


class MultipleSumSet
{
private:
	int m_n3Max{};
	int m_n5Max{};
	int m_sum3{};
	int m_sum5{};
	int m_totalSum{};

public:
	MultipleSumSet() : m_n3Max{ 1 }, m_n5Max{ 1 }, m_sum3{ 0 },
		m_sum5{ 0 }, m_totalSum{ 0 }
	{
	}

	MultipleSumSet(int& n) : m_sum3{ 0 }, m_sum5{ 0 }, m_totalSum{ 0 }
	{
		m_n3Max = static_cast<int>(floor(static_cast<double>(n) / 3));
		m_n5Max = static_cast<int>(floor(static_cast<double>(n) / 5));

		// In case one of the max multiples is actually equal
		// to n, we need to go to the next closest mutliple
		// by decrementing m_n3Max or m_n5max once.
		if (m_n3Max * 3 == n)
		{
			--m_n3Max;
		}
		if (m_n5Max * 5 == n)
		{
			--m_n5Max;
		}
	}

	int getn3Max() { return m_n3Max; }
	int getn5Max() { return m_n5Max; }
	int getsum3() { return m_sum3; }
	int getsum5() { return m_sum5; }
	int gettotalSum() { return m_totalSum; }

	void setnMaxes(int& a)
	{
		m_n3Max = static_cast<int>(floor(static_cast<double>(a) / 3));
		m_n5Max = static_cast<int>(floor(static_cast<double>(a) / 5));
		if (m_n3Max * 3 == a)
		{
			--m_n3Max;
		}
		if (m_n5Max * 5 == a)
		{
			--m_n5Max;
		}
	}

	int calculateSum3()
	{
		for (int n3counter{ 1 }; n3counter <= m_n3Max; ++n3counter)
		{
			m_sum3 += n3counter * 3;
		}

		return getsum3();
	}

	int calculateSum5()
	{
		for (int n5counter{ 1 }; n5counter <= m_n5Max; ++n5counter)
		{
			m_sum5 += n5counter * 5;
		}

		return getsum5();
	}

	// Note we only need to initailize this object and call
	// this one function in main!
	int calculateTotalSum()
	{
		m_totalSum = (calculateSum3()) + (calculateSum5());
		return gettotalSum();
	}

	void resetSums()
	{
		m_sum3 = 0;
		m_sum5 = 0;
		m_totalSum = 0;
	}
};


int main()
{
	// Ask for nMax (e.g. 10, 1000):
	std::cout << "Enter the maximum natural number (integer) "
		<< "below which to sum multiples of 3 and 5: ";
	int nMax{};
	std::cin >> nMax;

	// Initialize the MultipleSumSet object using nMax
	// to set m_n3Max and m_n5max:
	MultipleSumSet sumSetn{ nMax };

	// Now, we call the member function calculateTotalSum(),
	// which internally calls the other two sum functions.
	// We print the result using the same line:
	std::cout << "The sum of all mutliples of 3 or 5 below "
		<< nMax << " is equal to " << sumSetn.calculateTotalSum()
		<< "." << '\n';

	// Some debugging outputs to be used as needed:
	/*std::cout << "sum3 = " << sumSetn.getsum3() << '\n';
	std::cout << "sum5 = " << sumSetn.getsum5() << '\n';
	std::cout << "n3max = " << sumSetn.getn3Max() << '\n';
	std::cout << "n5max = " << sumSetn.getn5Max() << '\n';*/

	return 0;
}