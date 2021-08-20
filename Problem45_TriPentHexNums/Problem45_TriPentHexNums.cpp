/*
Program to identify the next triangular number
that is simultaneously pentagonal and hexagonal
after T_285 = P_165 = H_143 = 40755.

Note that each type is generated by a formula:
    Tri: T_n = n (n + 1) / 2
    Pent: P_n = n (3n - 1) / 2 
    Hex: n (2n - 1)
Such that, e.g.:
    Tri: 1, 3, 6, 10, 15, ...
    Pent: 1, 5, 12, 22, 35, ...
    Hex: 1, 6, 15, 28, 45, ...

Firstly, note we want the "next" value of T_n
past T_285 (i.e. we start with n=285 in our search).
We can then sweep T_n values above this, but we
need a means of confirming that a number is
pentagonal and hexagonal.  We force the number
being triangular by only considering triangular
numbers.  Similarly, given that the number we'll be
looking for is larger, it's sensible to note that
we can start looking for pentagonal and hexagonal
matches above P_165 and H_143, respectively.

It makes sense to implement the following:
    1) Function to calculate triangular numbers.
    2) Function to check if a number is pentagonal.
    3) Function to check if a number is hexagonal.
Note 2) and 3) could run for loops and check against
the input value (this minimizes use of memory).
    

NOTE: At current this code works fine, but it
may be too convoluted and could possibly be
simplified in the future.
*/

#include <cstdint>
#include <iostream>

using largeint_t = int_fast64_t;


/* Function to calculate triangular numbers: */
largeint_t calculateTriNum(largeint_t& n)
{
    return ( (n * ( n + 1 ) ) / 2 );
}

/* Function to check for pentagonal status
   and return the n value for P_n if yes;
   returns 0 if not found. */
largeint_t checkPentNum(largeint_t& triVal)
{
    largeint_t pentVal{};

    for (largeint_t p{ 165 }; p <= 100000; ++p)
    {
        pentVal = ((p * (3 * p - 1)) / 2);

        /* Ignore further p values if pentVal
        exceeds triVal and return as 0: */
        if (pentVal > triVal)
        {
            return 0;
        }

        /* Return p if we find a match to triVal: */
        if (pentVal == triVal)
        {
            return p;
        }
    }

    /* Throws an exception in main() that upper
    bound of p is too small (only way to reach
    this point).*/
    return -1;
}


/* Function to check for Hexagonal status
   and return the n value for H_n if yes;
   returns 0 if not found. */
largeint_t checkHexNum(largeint_t& triVal)
{
    largeint_t hexVal{};

    for (largeint_t h{ 143 }; h <= 100000; ++h)
    {
        hexVal = (h * (2 * h - 1) );

        /* Ignore further h values if pentVal
        exceeds triVal and return as 0: */
        if (hexVal > triVal)
        {
            return 0;
        }

        /* Return h if we find a match to triVal: */
        if (hexVal == triVal)
        {
            return h;
        }
    }

    /* Throws an exception in main() that upper
    bound of h is too small.*/
    return -1;
}


int main()
{
    /*
    Initialize a variable for triangular values,
    set by a for loop for n values starting at 285:
    */
    largeint_t triValue{};
    largeint_t triN{ 0 };
    largeint_t pentN{};
    largeint_t hexN{};

    /* DEBUG NOTE: for the purposes of testing the
    functions and this code, one can start n at
    285, which automatically outputs the 40755
    values. */

    for (largeint_t n{ 286 }; n <= 100000; ++n)
    {
        /* Get triangular number and check it
        for pentagonal and hexagonal status
        via functions: */
        triValue = calculateTriNum(n);

        pentN = checkPentNum(triValue);
        hexN = checkHexNum(triValue);

        /* Exceptions thrown when p, h ranges
        are too small in the check functions: */
        try
        {
            if (pentN == -1)
                throw "in checkPentNum(): p upper bound too small; no valid return";

            if (hexN == -1)
                throw "in checkHexNum(): h upper bound too small; no valid return";
        }
        catch (const char* exception)
        {
            std::cerr << "ERROR " << exception << ".\n";
        }


        /* Checks for pentagonal/hexagonal status.
        Note the 'check' function return 0 for
        a triValue that isn't pent or hex. */
        if (pentN > 0 && hexN > 0)
        {
            /* If true, we've found the next valid
            tri, pent, hex number, so record the
            n values for T_n, P_n, H_n and break
            the loop:*/
            triN = n;
            break;
        }
    }


    /* Exception in the case where we do not find
    the next number for n <= 1000; i.e. in that
    case we must increase the upper bound of n in
    the loop. */
    try
    {
        if (triN == 0)
            throw "No tri, pent, hex number was found below the upper bound of n.";
    }
    catch (const std::string& str)
    {
        std::cerr << "Error: " << str << '\n';
    }


    /* Print the next tri/pent/hex value to the user: */
    if (triN > 0 && pentN > 0 && hexN > 0)
    {
    std::cout << "The next triangular, pentagonal, hexagonal number above 40755 "
        << "was found to be T_" << triN << " = P_" << pentN << " = H_" << hexN
        << " = " << triValue << ".\n";
    }
    
    
    return 0;
}