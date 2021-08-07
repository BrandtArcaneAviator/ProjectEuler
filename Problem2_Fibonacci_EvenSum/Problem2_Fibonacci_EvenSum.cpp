// Program to calculate the sum of even valued terms
// in the Fibonacci sequence (starting with 1,2, add
// previous two terms to get next term) up to Fibonacci
// sequence values that do not exceed four million
// (4E6).
// 
// This can be done by running a for loop that holds
// four variables in memory, the sum variable (fibSum), 
// the previous two Fibonacci numbers (valFib1, valFib2,
// needed to calculate the next term in sequence)
// and the calculated next number in the sequence.
// Notably, in each instance of the loop,
// we need to check whether the new calculated Fibonacci
// number is even by using the modulus:
	// First, calculate newFib using two previous Fib numbers.
	// if(newFib % 2 == 0), then add newFib to sum.
//
// After we deal with the sum, we need to shift down the
// Fibonacci sequence to free up the calculation variable
// (i.e., newFib).  Thus, at the end of the loop, we set:
	// valFib1 = valFib2;  Shift valFib2 down once to 
		// first place, deleting valFib1's original value. 
	// valFib2 = newFib;  Shift newFib into second place.
	// newFib = 0;  
		// ^^^ Resets newFib s.t. next loop it can be 
		// calculated using the new values of valFib1 
		// and valFib2.
//
// This loop should be run until a newFib value that equals or
// exceeds the maximum limit in the sequence (here 4E6),
// s.t. using newFib as a conditional in a do-while loop 
// is sufficient, i.e.:
	// do()
	// while(newFib < 4E6)
// I should note that since we want to initialize valFib1
// and valFib2 using 1 and 2 respectively (s.t. first
// newFib is 3), we MUST initialize the sum variable to 2
// to account for valFib2's initial value.  We'll also
// use a fibMax value in main() to set the upper limit for the
// while loop manually for debugging purposes.
// 
// Lastly, I'll note that since we reset newFib each time in
// the loop, this newFib value needs to be checked in the
// while loop condition.  However, this also means we
// may go over (i.e. newFib >_ fibMax is still potentially
// added before the condition is checked) if we aren't careful.

#include <cstdint>
#include <iostream>

using largeint_t = int_fast32_t;

class FibonacciSumSet
{
private:
	largeint_t m_valFib1{};
	largeint_t m_valFib2{};
	largeint_t m_newFib{};
	largeint_t m_fibSum{};

public:
	FibonacciSumSet() : m_valFib1{ 1 }, m_valFib2{ 2 },
		m_newFib{ 0 }, m_fibSum{ 2 }
	{
	}

	// Not used here, but for ranges not starting with 1,2:
	//FibonacciSumSet(largeint_t& fib1, largeint_t fib2 ) 
	//	: m_valFib1{ fib1 }, m_valFib2{ fib2 }, m_newFib{0}
	//{
	//	// Note that in the Fibonacci sequence, since you
	//	// add odd + even = odd and eventually will end up
	//	// with odd + odd = even when you shift the sequence,
	//	// we need to carefully pick the initial value of
	//	// the sum according to whether fib1, fib2, or neither
	//	// is even.
	//	if (fib1 % 2 == 0)
	//	{
	//		m_fibSum = fib1; // i.e. fib1 is even, account in sum.
	//	}
	//	else if (fib2 % 2 == 0)
	//	{
	//		m_fibSum = fib2; // i.e. fib1 is odd, fib 2 is even.
	//	}
	//	else
	//	{
	//		m_fibSum = 0; // i.e. fib1 and fib2 are odd, exclude from sum.
	//	}
	//}

	largeint_t& getvalFib1() { return m_valFib1; }
	largeint_t& getvalFib2() { return m_valFib2; }
	largeint_t& getnewFib() { return m_newFib; }
	largeint_t& getfibSum() { return m_fibSum; }

	void calculatenewFib()
	{
		m_newFib = (getvalFib1() + getvalFib2());
	}

	void resetnewFib() { m_newFib = 0; }

	void shiftFibSequence()
	{
		m_valFib1 = m_valFib2;
		m_valFib2 = m_newFib;
		resetnewFib();
	}

	void addEvenNewFibToSum()
	{
		if (getnewFib() % 2 == 0)  // If newFib is even,
			m_fibSum += getnewFib(); // add it to sum.
	}

};

int main()
{
	// Set maximum upper limit for Fib sequence (values < this):
	// largeint_t fibMax{100}; 
		// ^^^ Debug value, should yield 44 for sum.
	largeint_t fibMax{ static_cast<largeint_t>(4e6) };

	// Initialize the FibonacciSumSet and manually push
	// the first newFib calculation:
	FibonacciSumSet FibSumSet{}; // sets newFib = 0; fibSum =2.
	FibSumSet.calculatenewFib(); // i.e. sets newFib = 3.

	// Set up the printout:
	std::cout << "For values in the Fibonacci sequence "
		<< "starting with " << FibSumSet.getvalFib1() << ", "
		<< FibSumSet.getvalFib2() << " that are below "
		<< fibMax << ", the sum of the even values in "
		<< "the sequence is: ";

	// Note this is checking the previous loop's newFib,
	// such that we ONLY reset newFib and shift the sequence
	// at the start of this loop and NOT at the end, where
	// it would have reset newFib! Otherwise we can't check
	// newFib in the while loop condition.
	while (FibSumSet.getnewFib() < fibMax)
	{
		// Now that we know newFib < FibMax, check for
		// even newFib and if so add to sum:
		FibSumSet.addEvenNewFibToSum();

		// Shift to next part of sequence:
		FibSumSet.shiftFibSequence();

		// Calculate the next newFib:
		FibSumSet.calculatenewFib();
	}

	// After the sum completes (i.e., the while loop ends)
	// print total sum to screen:
	std::cout << FibSumSet.getfibSum() << ".\n";

	return 0;
}