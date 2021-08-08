// Program to identify three natural numbers, a, b, c,
// which satisfy:
	// i) a < b < c
	// ii) a^2 + b^2 = c^2
	// iii) a + b + c = 1000
// Once the set of numbers is identified, we find the
// product abc.

// Since 1000 is the value that sets the "special pythagorean
// triplet" ( a normal one satisfies only i), ii)), we'll
// replace 1000 with a value called Nspec.

#include <cassert>
#include <iostream>

// Class object to manipulate a Special Pythagorean Triplet:
class SpecPythagTriplet
{
private:
	int m_a{};
	int m_b{};
	int m_c{};
	int m_abcSum{};
	int m_abcProduct{};
	int m_Nspec{};

public:
	SpecPythagTriplet() : m_a{ 0 }, m_b{ 0 }, m_c{ 0 },
		m_abcSum{ 0 }, m_abcProduct{ 0 }, m_Nspec{ 0 }
	{
	}

	SpecPythagTriplet(int& n1) : m_a{ 0 }, m_b{ 0 }, m_c{ 0 },
		m_abcSum{ 0 }, m_abcProduct{ 0 }, m_Nspec{ n1 }
	{
	}

	SpecPythagTriplet(int& a, int& b, int& c, int& n) : m_a{ a },
		m_b{ b }, m_c{ c }, m_abcSum{ (a + b + c) },
		m_abcProduct{ (a * b * c) }, m_Nspec{ n }
	{
	}

	int& geta() { return m_a; }
	int& getb() { return m_b; }
	int& getc() { return m_c; }
	int& getabcSum() { return m_abcSum; }
	int& getabcProduct() { return m_abcProduct; }
	int& getNspec() { return m_Nspec; }

	void seta(int& a1) { m_a = a1; }
	void setb(int& b1) { m_b = b1; }
	void setc(int& c1) { m_c = c1; }
	void setNspec(int& n) { m_Nspec = n; }

	void setSumAndProduct()
	{
		m_abcSum = (geta() + getb() + getc());
		m_abcProduct = (geta() * getb() * getc());
	}

	// Checks condition i) a < b < c:
	bool checkaLTbLTc()
	{
		if ((geta() < getb()) && (getb() < getc()))
			return true;
		else
			return false;
	}

	// Checks condition ii) a^2 + b^2 = c^2:
	bool checkPythagTrip()
	{
		if (((geta() * geta()) + (getb() * getb())) == (getc() * getc()))
			return true;
		else
			return false;
	}

	// Checks condition iii) a + b + c = Nspec:
	bool checkSpecialSum()
	{
		setSumAndProduct();

		if (getabcSum() == getNspec())
			return true;
		else
			return false;
	}

	// Function to check all conditions at once:
	bool checkSpecPythagTrip()
	{
		if (checkaLTbLTc() && checkPythagTrip() && checkSpecialSum())
			return true;
		else
			return false;
	}
};


int main()
{
	// Initialize a SpecPythagTriplet object with a chosen
	// Nspec (using 2nd constructor):
	std::cout << "Enter a (positive) natural number which the "
		<< "sum a + b + c of a Pythagorean triplet (a,b,c) is equl to: ";
	int n{};
	std::cin >> n;

	SpecPythagTriplet spTriplet{ n };

	// Now that we have our condition iii) set, we run
	// a series of nested for loops for values of a,b,c.
	// Note this is done more efficiently by recognizing that
	// condition i) means that the for loop for a has range
	// 1 <= a < b, and similarly for b, 1 <= b < c.
	// Note, given condition ii), we do not check negative
	// values for a,b,c.
	// We can also note that the max range for the loop over
	// values of c cannot be larger than the sum of a,b,c
	// set in condition iiI), i.e. Nspec or n here.

	// Boolean to note when we've found the right a,b,c
	// that gives the Special Pythagorean Triplet.
	bool isSpecPythagTrip{ false };

	// Loop for values of c:
	for (int counterC{ 1 }; counterC < n; ++counterC)
	{
		spTriplet.setc(counterC);

		// Loop for values of b:
		for (int counterB{ 1 }; counterB < counterC; ++counterB)
		{
			spTriplet.setb(counterB);

			// Loop for values of a:
			for (int counterA{ 1 }; counterA < counterB; ++counterA)
			{
				spTriplet.seta(counterA);

				// Now we check the conditions for Special
				// Pythagorean Triplet (i)-iii));
				// if true, we've found the correct a,b,c,
				// and we can end the loops.
				if (spTriplet.checkSpecPythagTrip())
				{
					isSpecPythagTrip = true;
					break;
				}

			}
			if (isSpecPythagTrip)
				break;
		}
		if (isSpecPythagTrip)
			break;
	}

	// Once we exist loop, a,b,c should be the correct values
	// for the Special Pythagorean Triplet.  If the boolean
	// is still false, then no such triplet was found:
	if (isSpecPythagTrip)
	{
		std::cout << "The Special Pythagorean Triplet ("
			<< spTriplet.geta() << ", " << spTriplet.getb()
			<< ", " << spTriplet.getc() << "), whose sum equals "
			<< spTriplet.getNspec() << ", has the product abc = "
			<< spTriplet.getabcProduct() << ".\n";
	}
	else
	{
		std::cout << "No Special Pythagorean Triplet was found "
			<< "whose sum (a + b + c) equals " << spTriplet.getNspec()
			<< ".\n";
	}

	return 0;
}