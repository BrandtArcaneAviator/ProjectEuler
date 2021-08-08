// Program to identify the first number in a Collatz
// sequence (with a value starting under one million,
// though later elements can be greater than one million)
// that produces the longest chain.  Note that a Collatz
// sequence entails:
	// For a positive integer n in the sequence:
	// i) If n = even, then n -> n/2 (next number in sequence).
	// ii) If n = odd, then n -> 3n +1
// It is thought that using this that eventually, the 
// sequence will reach a value of 1, which here is the 
// end condition for a given Collatz sequence.
// 
// Therefore, we want to count the number of iterations
// in the sequence up to the point where the sequence reaches
// a value of 1, and then try to find a starting value that
// maximizes this counter's value.  Note this means we need
// to a) track the starting values of the sequence and
// b) track the number of interation (counts) for a given
// starting value, and importantly, c) be able to compare
// values (NOTE WE MUST COMPARE ALL STARTING VALUES UP TO
// ONE MILLION TO DO THIS CORRECTLY).
// 
// Thus, we need to have two vectors with correlating 
// starting values and maximum counts (we implement this as
// std::vectors acting as stacks in a class object), where
// a given position in one vector directly relates to the same
// position in another.
// 
// Thankfully, we can run individual Collatz sequences and 
// the counting of steps within a self-contained while loop
// for each given starting value, using a member function.
// 
// Then, in main(), we first set the maximum starting number
// (ideally we want to test 1e6, i.e. a million, but we do
// this for debugging purposes), initialize the class object,
// and then run a for loop across the starting values.
// Note again to properly get the longest chain, we need to
// test and compare all values between 1 and the max starting
// number (this means the vector will get quite long,
// capacity will need to be dynamically set, and
// there are memory leak concerns here).
//

#include <algorithm> // For *max_element() search function.
#include <cstdint> // For fast, large integer types
#include <iostream>
#include <vector> // for std::vector

using largeint_t = std::int_fast64_t;

class CollatzSequenceSet
{
private:
	std::vector<largeint_t> m_startVector{};
	std::vector<largeint_t> m_countVector{};
	largeint_t m_maxStartVal{};
	largeint_t m_sequenceStartVal{};
	largeint_t m_sequenceVal{};
	largeint_t m_sequenceCount{};

public:
	CollatzSequenceSet() :
		m_maxStartVal{ 1 }, m_sequenceStartVal{ 1 },
		m_sequenceVal{ m_sequenceStartVal }, m_sequenceCount{ 0 }
	{
		// We implement the vector capacities this way
		// so that the utilized memory is FIXED by maxStartVal
		// and does not have the risk of unlimited dynamic
		// memory allocation.
		m_startVector.reserve(m_maxStartVal);
		m_countVector.reserve(m_maxStartVal);
	}

	CollatzSequenceSet(largeint_t& maxStartVal) :
		m_maxStartVal{ maxStartVal }, m_sequenceStartVal{ 1 },
		m_sequenceVal{ m_sequenceStartVal }, m_sequenceCount{ 0 }
	{
		m_startVector.reserve(maxStartVal);
		m_countVector.reserve(maxStartVal);
	}

	largeint_t& getmaxStartVal() { return m_maxStartVal; }
	largeint_t& getsequencestartVal() { return m_sequenceStartVal; }
	largeint_t& getsequenceVal() { return m_sequenceVal; }
	largeint_t& getsequenceCount() { return m_sequenceCount; }

	std::vector<largeint_t>& getstartVector() { return m_startVector; }
	std::vector<largeint_t>& getcountVector() { return m_countVector; }

	void setmaxStartVal(largeint_t& maxStartVal1)
	{
		m_maxStartVal = maxStartVal1;
		// Because we've changed this here, we need to resize
		// the vector objects as well:
		m_startVector.reserve(maxStartVal1);
		m_countVector.reserve(maxStartVal1);
	}

	void incrementsequenceStartVal() { ++m_sequenceStartVal; }
	void resetsequenceStartVal() { m_sequenceStartVal = 1; }
	void incrementsequenceVal() { ++m_sequenceVal; }
	void resetsequenceVal() { m_sequenceVal = m_sequenceStartVal; }
	void incrementsequenceCount() { ++m_sequenceCount; }
	void resetsequenceCount() { m_sequenceCount = 0; }

	// Member function to count the # of iterations in
	// a given Collatz sequence that begins with a
	void countCurrentCollatzSequence()
	{
		// First, we need to record the starting value in
		// the vector, using it like a stack:
		m_startVector.push_back(getsequencestartVal());

		// Now we need to run through the sequence and count
		// the number of iterations in the while loop using
		// m_sequenceCount.
		while (getsequenceVal() != 1)
		{
			// Now we check if the current value in sequence
			// is even or odd:
			if (getsequenceVal() % 2 == 0) // i.e. even:
			{
				m_sequenceVal = (m_sequenceVal / 2);
			}
			else // i.e. odd:
			{
				m_sequenceVal = ((3 * m_sequenceVal) + 1);
			}
			// And note we did a step in the sequence:
			incrementsequenceCount();
		}

		// At the end here, we need to record the maximum
		// count value, reset this count value for the next 
		// loop, and move on to the next starting value, 
		m_countVector.push_back(getsequenceCount());
		resetsequenceCount();
		incrementsequenceStartVal();
		resetsequenceVal();
	}

	// Function to run all counting processes to fill out
	// the member std::vector variables; runs from 1 up
	// to m_maxStartVal.
	void countAllStartValues()
	{
		while (getsequencestartVal() <= m_maxStartVal)
		{
			countCurrentCollatzSequence();
		}

		// Now that we have run all start values up to maxStartVal,
		// we can reset m_sequenceStartVal:
		resetsequenceStartVal();
	}

	// Member fucntions which finds and returns the starting
	// value (in the range 1 to maxStartVal) which yields 
	// the longest chain (by finding the position of the 
	// largest value in countVector, and then using that
	// position in the startVector to find the corresponding
	// start value).
	// Should only be called AFTER running countAllStartValues().
	largeint_t findLongestChainStartVal()
	{
		return m_startVector.at((std::max_element(m_countVector.begin(), m_countVector.end()) - m_countVector.begin()));
	}

	largeint_t findLongestChainCountVal()
	{
		return m_countVector.at((std::max_element(m_countVector.begin(), m_countVector.end()) - m_countVector.begin()));
	}
};


int main()
{
	// First, we ask user to enter the cap for starting numbers
	// (e.g. 1e6, or one million is what is entered here):
	std::cout << "Enter the maximum number below which to "
		<< "check starting values in Collatz sequences: ";
	largeint_t maxStartCap{};
	std::cin >> maxStartCap;
	// We need just below this cap for m_maxStartVal:
	--maxStartCap;

	// Now we initialize the class object:
	CollatzSequenceSet csSet{ maxStartCap };

	// Now we need to run the member function countAllStartValues
	// to fill out the vectors therein:
	csSet.countAllStartValues();

	// Now we can ask for the starting value (and/or count value)
	// for which we have maximized the count value (i.e. the
	// longest chain), and print this back to the user:
	std::cout << "The starting value below " << (maxStartCap + 1)
		<< " which produces the longest chain in a Collatz "
		<< "sequence was found to be " << csSet.findLongestChainStartVal()
		<< ", with a chain " << csSet.findLongestChainCountVal()
		<< " long.\n";

	return 0;
}