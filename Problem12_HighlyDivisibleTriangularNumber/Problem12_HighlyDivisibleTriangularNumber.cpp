// !!!!!!! Currently doesn't work for large # of divisors
// (e.g. 500 runs for more than an hour, while 250 runs
// in under a few minutes), and probably NEEDS optimization.

// Program to identify the value of the first triangular
// number which has over five hundred divisors (i.e. factors).
// 
// Firstly, note that a triangular number Ntriag is one where:
    // 1 + 2 + 3 + ... = Ntriag
    // e.g. the 7th Ntriag is: 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28.
// Therefore, we can express the values of Ntriag using a sum:
    // Ntriag = sigma^N_1 ( N )
    // i.e. sum the values from 1 to N, for a given N.
//
// Next, we need to identify the factors of a given Ntriag.
// To do so, we note that a "factor" is evenly divisible into
// a given Ntriag, such that Ntriag % (factor) = 0.  If we
// find a factor, we should count it using a counter (called
// factorCounter).  
// 
// Since we are looking for the first
// triangular number with more than five hundred divisors, we
// need to implement two while loops checking i) a given Ntraig
// for ii) more than five hundred divisors.  
// The outer loop will shift through various values of Ntriag 
// (note that this means the N value in the sum above is equal
// to the counter of this loop, this enters the class 
// TriangularNumberSet object as nMax), while the inner counts up the
// number of evenly divisible factors of Ntriag until either
// a) the factor value reaches the value of Ntriag (i.e.
// divide 28 by 28, for example, means 28 is the last factor of
// Ntriag=28) or until we find more than five hundred divisors
// (i.e. the factorCounter value exceeds 500).

#include <cstdint>
#include <iostream>

using largeint_t = int_fast64_t;

class TriangularNumberSet
{
private:
    largeint_t m_nMax{};
    largeint_t m_nTriag{};
    largeint_t m_factor{};
    largeint_t m_maxFactors{};
    largeint_t m_factorCounter{};

public:
    TriangularNumberSet() : m_nMax{ 1 }, m_nTriag{ 1 },
        m_factor{ 1 }, m_maxFactors{ 1 }, m_factorCounter{ 0 }
    {
    }

    TriangularNumberSet(largeint_t nMax1, largeint_t& maxFactors) :
        m_nMax{ nMax1 }, m_factor{ 1 }, m_maxFactors{ maxFactors },
        m_factorCounter{ 0 }
    {
        m_nTriag = 0;
        for (largeint_t i{ 1 }; i <= m_nMax; ++i)
            m_nTriag += i;
    }

    largeint_t& getnMax() { return m_nMax; }
    largeint_t& getnTriag() { return m_nTriag; }
    largeint_t& getfactor() { return m_factor; }
    largeint_t& getmaxFactors() { return m_maxFactors; }
    largeint_t& getfactorCounter() { return m_factorCounter; }

    void setnMax(largeint_t& nMax) { m_nMax = nMax; }
    void setnTriag()
    {
        m_nTriag = 0;
        for (largeint_t a{ 1 }; a <= getnMax(); ++a)
            m_nTriag += a;
    }

    void calculatenTriag(largeint_t& nMax2)
    {
        setnMax(nMax2);
        setnTriag();
    }

    void setmaxFactors(largeint_t& maxFactors1) { m_maxFactors = maxFactors1; }

    void incrementfactor() { ++m_factor; }
    void resetfactor() { m_factor = 1; }

    void incrementfactorCounter() { ++m_factorCounter; }
    void resetfactorCounter() { m_factorCounter = 0; }

    bool checkMaxFactors()
    {
        // Returns true if factorCounter counts more than
        // the required factors (divisors) of nTriag:
        if (getfactorCounter() > getmaxFactors())
            return true;
        else
            return false;
    }

    // This is the implementation of the inner loop,
    // where we count the number of factors of a given Ntriag.
    largeint_t& countNumberOfFactors()
    {
        while (m_factor <= m_nTriag)
        {
            if ((m_nTriag % m_factor) == 0)
            {
                incrementfactorCounter();
            }

            if (checkMaxFactors())
            {
                break;
            }
            else
            {
                incrementfactor();
            }
        }

        return getfactorCounter();
    }
};


int main()
{
    // Initialize a Triagular number Set object
    // which starts at N=1 and has maxFactors set by
    // the user:
    std::cout << "Enter how many divisors a triangular number "
        << "must have to exceed: ";
    largeint_t maxFact{};
    std::cin >> maxFact;

    // Fixed maximum N value to try:
    largeint_t maxN{ 10000000000 };

    // Boolean which becomes true when first valid
    // triangular number with more factors than max factors
    // is found (i.e. starts false).
    bool isnTriagWithMoreThanMaxFactors{ false };

    TriangularNumberSet tnSet{ 1, maxFact };

    // Outer for loop which runs over various values of
    // nTriag according to the counter for the Nth triangular
    // number:
    for (largeint_t counterN{ 1 }; counterN < maxN; ++counterN)
    {
        // Find the counterN-th nTriag:
        tnSet.calculatenTriag(counterN);

        // Now count the number of factors in this nTriag:
        tnSet.countNumberOfFactors();

        // And check if this number exceeds maxFactors:
        if (tnSet.checkMaxFactors())
        {
            isnTriagWithMoreThanMaxFactors = true;
            break;
        }
        else
        {
            // If it doesn't, go onto next counterN, noting
            // that we must reset both m_factor and m_factorCounter:
            tnSet.resetfactor();
            tnSet.resetfactorCounter();
        }
    }

    // If we've reached this point, either a) we've found
    // the first nTriag which satisfies checkMaxFactors,
    // or we've broken the upper limit of the above for loop.
    // Thus, we report back to user the nTriag value or
    // we give an error for not finding one:
    if (isnTriagWithMoreThanMaxFactors)
    {
        std::cout << "The first triangular number which has "
            << "more than " << tnSet.getmaxFactors() << " divisors "
            << "has value " << tnSet.getnTriag() << ".\n";
    }
    else
    {
        std::cout << "Error: no triangular number below the "
            << maxN << "-th triangular number was found to have "
            << "more than " << tnSet.getmaxFactors() << " divisors.\n";
    }

    return 0;
}