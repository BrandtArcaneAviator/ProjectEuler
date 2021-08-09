// Currently yields incorrect values for StealthNum,
// likely due to recounting unique sets of a,b,c,d.
// This is slightly remedied by the use of additional
// if statements, but the code still doesn't seem
// to give correct values and runs rather slowly.
// 
// Program to determine the number of "stealthy" numbers,
// denoted the counter stealthNum, in the range 
// 1 <_ N <_ N_max for positive integer N as defined by 
// the conditions:
    // i) ab = cd = N, where a,b,c,d, are also positive
    // integers
    // ii) a + b = c + d + 1
// In this code, for each given N value, we force b = N/a 
// and d = N/c to hard code condition i) and reduce the 
// number of values needed when sweeping over values of 
// a,b,c,d (notably these all must be less than N by 
// condition i)).  Also note that by associativity
// of multiplication, we prove ab = cd by showing
// ab = N and cd = N.
// 
// We then check condition ii) by checking a + b = c + d + 1,
// (which only excludes the cases (a=c, b=d) and
// (a=d, b=c) if we also check that ab = cd, which double 
// checks i)).  If this condition is satisfied,
// then we have found a stealthy number, we increment
// stealthNum and move to the next N value.  These loops
// are repeated for all values of N in the given range.

#include <cstdint>
#include <iostream>

using largeint_t = std::int_least64_t;

// Class for bundling a, b, c, d, for given value of N.
// Includes an extra boolean value that determines if the
// number set corresponds to a stealthy number.
class StealthNumSet
{
private:
    largeint_t m_n{};
    largeint_t m_a{};
    largeint_t m_b{};
    largeint_t m_c{};
    largeint_t m_d{};
    bool m_bool{};

public:
    StealthNumSet()
        : m_n{ 1 }, m_a{ 1 }, m_b{ 1 }, m_c{ 1 }, m_d{ 1 },
        m_bool{ false }
    {
    }

    StealthNumSet(largeint_t& N, largeint_t& a, largeint_t& c)
        : m_n{ N }, m_a{ a }, m_b{ (N / a) }, m_c{ c }, m_d{ (N / c) },
        m_bool{ false }
    {
    }

    largeint_t getN() { return m_n; }
    largeint_t geta() { return m_a; }
    largeint_t getb() { return m_b; }
    largeint_t getc() { return m_c; }
    largeint_t getd() { return m_d; }
    bool getBool() { return m_bool; }

    void setN(largeint_t& n1) { m_n = n1; }
    void setab(largeint_t& a1)
    {
        m_a = a1;
        m_b = (m_n / a1);
    }
    void setcd(largeint_t& c1)
    {
        m_c = c1;
        m_d = (m_n / c1);
    }

    // Checks condition ii) for stealthy numbers.
    // Note condition i) is fully forced by the 
    // set functions and the second constructor, i.e.
    // they show ab = N and cd = N and thus ab = cd is true.
    // Also note the cases (a=c, b=d), (a=d,b=c) are
    // automatically excluded by this if statement when
    // we include ab = cd as a secondary condition.
    // Duplicate combinations of a,b,c,d are a problem though!
    // To avoid recounting, we need to force a <= b and c <= d
    // (e.g. to avoid recounting N=4, we note the 1,4,2,2 and 
    // 4,1,2,2 permutations are identical) such that a,b and 
    // c,d don't overshare values.  We implement this as 
    // an if statement inside the other. 
    // 
    // We also need to address duplication between sets of
    // a,b and c,d (e.g. for N=4 above, 2,2,1,4 is a 
    // duplicate of 1,4,2,2). Since a and c set b and d,
    // we can avoid this by also forcing a <= c (in which
    // case, only the 1,4,2,2 variant will be counted).
    // We implement this as the condition cCounter <= aCounter
    // in the for loop in main (this reduces # of calcs
    // significantly).
    //
    // If this function returns true, then the loops over a,
    // c should be ended and we step to the next N.  While
    // m_bool is false, both loops continue. 
    bool checkStealth()
    {
        // Checks condition ii) only, since i) is forced.
        if (((m_a + m_b) == (m_c + m_d + 1)) && ((m_a * m_b) == (m_c * m_d)))
        {
            // Avoids duplicate variations between a,b and 
            // c,d values.
            if ((m_a <= m_b) && (m_c <= m_d))
            {
            m_bool = true; // Implies N is stealthy number.
            }
        }
        else
        {
            m_bool = false;
        }

        return m_bool;
    }

    void resetBool() { m_bool = false; }
};



int main()
{
    // Request the maximum upper bound for N from user:
    std::cout << "Enter the maximum value of N (positive integer): "
        << '\n';
    largeint_t nMax{};
    std::cin >> nMax;

    largeint_t stealthNum{ 0 }; // counter for total # of stealhy numbers

    // Create our stealth number set object, which we will
    // use as the memory bank for the values as we sweep
    // through them (we replace values in this object as we
    // sweep so they only have one value at a time).
    StealthNumSet numSetN{};

    // Tell user it's working on it:
    std::cout << "Calculating..." << '\n';

    // Loop over N, from 1 up to (but not at) N_max:
    for (largeint_t nCounter{ 1 }; nCounter < nMax; ++nCounter)
    {
        numSetN.setN(nCounter);

        // Loop over c, from 1 to the current N:
        for (largeint_t cCounter{ 1 }; cCounter <= nCounter; ++cCounter)
        {
            numSetN.setcd(cCounter); // Sets a,b, in the object

            // Loop over a, from 1 to the current a.
            // Uses cCounter to avoid duplicate sets of a,b,c,d.
            for (largeint_t aCounter{ 1 }; aCounter <= cCounter; ++aCounter)
            {
                numSetN.setab(aCounter); // Sets c,d in the object

                // If this number set is stealthy:
                if (numSetN.checkStealth())
                {
                    ++stealthNum; // increment stealthNum
                    break;
                }
            }

            if (numSetN.getBool())
            {
                break;
            }
        }

        numSetN.resetBool();
    }

    // Now we output the number of stealthy numbers below
    // Nmax to the screen:
    std::cout << "There are " << stealthNum << " stealthy numbers that are less than "
        << nMax << "." << '\n';

    return 0;
}