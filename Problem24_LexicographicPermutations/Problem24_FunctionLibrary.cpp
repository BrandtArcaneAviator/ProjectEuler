/* Function Library for Problem 24,
   accessed through #include "Problem24_FunctionLibrary.h" */

#include "Problem24_FunctionLibrary.h"

/* Function to extract all digit values from the input string
   and return these as an std::vector<int>. */
std::vector<int> extractDigitstoVector(std::string str)
{
	std::vector<int> temp;

	for (auto i : str)
	{
		/* This ignores non - digit values, i.e.only
		accepts 0-9 values.*/
		if (isdigit(i))
		{
			temp.push_back(i - '0');
		}
	}

	/*
	Now we want this to initially sort the digits by value.
	We use a basic sort() algorithm for this.  This ensures
	the first correct permutation (e.g. 0123, or 0123456789).
	*/
	std::sort(temp.begin(), temp.end());

	return temp;
}

/* Function to print digits of the vector form into a
   returnable string buffer. */
std::ostringstream printcurrentDigits(std::vector<int> cpvec)
{
	std::ostringstream oss;
	for (auto a : cpvec)
	{
		oss << a;
	}

	return oss;
}

/*
Fuctions necessary to perform recursive permutations
of a given set of digits in the std::vector<int>.
*/

/* Function to remove a digit from a vector: */
std::vector<int> remove_digit(const std::vector<int>& vec1, const int& id)
{
	std::vector<int> tempRem;
	for (unsigned int b{ 0 }; b < vec1.size(); ++b)
	{
		if (b != id)
			tempRem.push_back(vec1.at(b));
	}
	return tempRem;
}

/* Function to add a digit to a vector: */
std::vector<int> add_digit(const std::vector<int>& vec1, const int& c)
{
	std::vector<int> tempAdd{ vec1 };
	tempAdd.push_back(c);
	return tempAdd;
}

/* Function to add a set of given permutations
   to another set of permutations. */
std::vector<std::vector<int>> merge_digitVec(const std::vector<std::vector<int>>& vecP1, const std::vector<std::vector<int>>& vecP2)
{
	std::vector<std::vector<int>> tempMerge{ vecP1 };
	for (const auto& d : vecP2)
	{
		/* This "merges" a permutation to another list of
		   permutations. */
		tempMerge.push_back(d);
	}
	return tempMerge;
}

/* Function to find all permutations up to the
   nth permutation for a given set of digits.
   Note that we call this without vec1,
   i.e. we are doing permutations of vec2 using an
   empty vec1.  Returns the full list of permutations,
   strangely in lexicographic order (NOT SURE WHY). */
std::vector<std::vector<int>> permutations(const std::vector<int>& vec2, const std::vector<int>& vec1 = {})
{
	if (vec2.empty())
		return { vec1 };

	std::vector<std::vector<int>> tempPerm;

	for (unsigned int i2{ 0 }; i2 < vec2.size(); ++i2)
	{
		tempPerm = merge_digitVec(tempPerm, permutations(remove_digit(vec2, i2), add_digit(vec1, vec2.at(i2))));
	}

	return tempPerm;
}