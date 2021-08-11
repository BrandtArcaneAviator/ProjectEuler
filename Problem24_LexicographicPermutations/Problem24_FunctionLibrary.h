#ifndef PROBLEM24_FUNCTIONLIBRARY_H
#define PROBLEM24_FUNCTIONLIBRARY_H

#include <algorithm> // For sort().
#include <cctype> // For isdigit().
#include <cstdint> // For large integer (non-digit) types.
#include <iostream>
#include <string> // For std::string.
#include <sstream> // For stringstream.
#include <vector>

std::vector<int> extractDigitstoVector(std::string str);

std::ostringstream printcurrentDigits(std::vector<int> cpvec);

std::vector<int> remove_digit(const std::vector<int>& vec1, const int& id);

std::vector<int> add_digit(const std::vector<int>& vec1, const int& c);

std::vector<std::vector<int>> merge_digitVec(const std::vector<std::vector<int>>& vecP1, const std::vector<std::vector<int>>& vecP2);

std::vector<std::vector<int>> permutations(const std::vector<int>& vec2, const std::vector<int>& vec1);

#endif