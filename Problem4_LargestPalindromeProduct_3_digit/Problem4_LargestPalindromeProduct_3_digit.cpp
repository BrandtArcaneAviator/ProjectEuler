// Program to calculate the largest Palindrome (i.e.
// reads the same forward and backwards) product produced
// by multiplying two 3-digit numbers.

// To do so, first we need to be able to identify a
// palindrome number, i.e. we need to be able to convert
// a given number (we'll focus only on integer products here)
// into a vector where we can identify that a(1) = a(N)
// (for a vector with N elements), a(1+1) = a(N-1),
// a(1+2) = a(N-2), etc. 

#include <algorithm> // for std::reverse on std::vector.
#include <iostream>
#include <vector> // for std::vector.

// Class to analyze whether a given product of
// two numbers is a Palindrome:
class PalindromeProduct
{
private:
	int m_numDigits{};
	int m_a{};
	int m_b{};
	int m_productab{};
	int m_transformProd{};
	std::vector<int> m_vector{};  //Length not initialized here.

public:
	// Normal constructor sets the lgenth of vector
	// to 6 (i.e. the largest product for 3-digit integers
	// is 999*999 = 998,001, a six digit number).
	PalindromeProduct() : m_numDigits{ 3 }, m_a{ 0 }, m_b{ 0 },
		m_productab{ 0 }, m_transformProd{ 0 }
	{
		m_vector.reserve(6);
	}

	// Constructor for abitrary digits:
	PalindromeProduct(int& numDigit) : m_numDigits{ numDigit },
		m_a{ 0 }, m_b{ 0 }, m_productab{ 0 },
		m_transformProd{ 0 }
	{
		m_vector.reserve(2 * m_numDigits);
	}

	int& getnumDigits() { return m_numDigits; }
	int& geta() { return m_a; }
	int& getb() { return m_b; }
	int& getproductab() { return m_productab; }
	std::vector<int>& getvector() { return m_vector; }

	void setnumDigits(int& numDig) { m_numDigits = numDig; }
	void seta(int& a) { m_a = a; }
	void setb(int& b) { m_b = b; }

	int& calculateProductab()
	{
		m_productab = m_a * m_b;
		return getproductab();
	}

	void transformProducttoVector()
	{
		// First, clear any previous numbers in the vector:
		m_vector.clear();
		m_vector.reserve(2 * getnumDigits());
		// ^^^ SETS CAPACITY OF m_vector, NOT LENGTH!

		// Next, assign new values of number to vector,
		// which requires transforming the int variable into
		// the vector form; we use an intermediate variable
		// for this purpose (transformProd).
		m_transformProd = m_productab;
		while (m_transformProd > 0)
		{
			// This sets vector length according to # of digits
			// in the product (CAN BE LESS THAN 2*m_numDigits!).
			m_vector.push_back(m_transformProd % 10);
			m_transformProd = static_cast<int>(floor(static_cast<double>(m_transformProd) / 10));
		}

		// However, note the above loop puts the vector in
		// backwards order (i.e. its 100,899 for 998,001 right
		// now), so we need to reverse the order of this vector:
		std::reverse(m_vector.begin(), m_vector.end());
		// Now its in its correct form (e.g., 998,001).
	}

	bool checkPalindrome()
	{
		// Use a for loop to check the values for
		// Palindrome.  Note we only need to check that
		// vector[0] = vector[5], vector[1] = vector[4]
		// and vector[2] = vector[3] for 6 digit products, e.g.
		// BUT, for odd digit numbers, we also will have to say,
		// e.g., vector[2] = vectpr[2] for a 5 digit product,
		// so for simplicity we simple check all variations here,
		// which is notably less efficient.
		for (int counter1{ 0 }; counter1 < m_vector.size(); ++counter1)
		{
			// If they don't match, then its not a Palindrome:
			if (m_vector[counter1] != m_vector[(m_vector.size() - (counter1 + 1))])
				return false;
		}

		// If loop succeeds, then the product is a Palindrome
		// and we return true:
		return true;
	}

	// Not used, but here is reset (does not reset m_numDigits):
	void resetPalindromeProduct()
	{
		m_a = 0;
		m_b = 0;
		m_productab = 0;
		m_transformProd = 0;
		m_vector.clear();
		m_vector.reserve(2 * getnumDigits());
	}
};


int main()
{
	// Initialize the Palindrome product object we'll
	// be modifying in the loop (for products of 3 digit
	// numbers):
	std::cout << "Enter the maximum number of digits "
		<< "you wish to find the largest palindrome product "
		<< "of (2 or 3): ";
	int x{};
	std::cin >> x;

	PalindromeProduct PalProduct{ x };

	// Need to perform a "backwards" for loop here,
	// counting down with two counters (the a and b
	// in the product) from the largest 3-digit number
	// (999) s.t. we more quickly identify the largest
	// palindrome product.  Note if we find a palindrome
	// we can immediately end the loop and print the
	// palindrome as the result (it will automatically be
	// the largest palindrome product this way).
	// In the outer loop (a), we set an a value using the
	// counter and then run the inner loop (b) for all
	// b values (999-001, remember we are counting backwards).
	// In the inner loop (b), we calculate the product ab
	// and check if it is a palindrome, in which case we break
	// out of both loops (requires 2 if statements!).  If
	// it isn't, then we change b and calculate the next 
	// product and check it, and so on.
	int counterA{};
	int counterB{};

	switch (PalProduct.getnumDigits())
	{
	case 2: {counterA = 99; counterB = 99; break; }
	case 3: {counterA = 999; counterB = 999; break; }
	}

	bool truePal{ false };

	for (; counterA > 1; --counterA)
	{
		// Set value of a:
		PalProduct.seta(counterA);

		for (; counterB > 1; --counterB)
		{
			// Set value of b:
			PalProduct.setb(counterB);

			// Now calculate ab:
			PalProduct.calculateProductab();

			// Now we must check if the product is a palindrome:
			PalProduct.transformProducttoVector();

			if (PalProduct.checkPalindrome())
			{
				truePal = true;
				break;
			}
		}

		// Required to break free of both loops if
		// a Palindrome is found:
		if (truePal)
		{
			break;
		}
	}

	if (truePal)
		std::cout << "The largest palindrome product of two "
		<< PalProduct.getnumDigits() << " digit numbers (integers) "
		<< "was found to be: " << PalProduct.geta() << " * "
		<< PalProduct.getb() << " = " << PalProduct.getproductab()
		<< ".\n";
	else // i.e. we fail to find ANY palindrome, s.t. code is bad:
		std::cout << "Error: no palindrome product was found."
		<< '\n';

	return 0;
}