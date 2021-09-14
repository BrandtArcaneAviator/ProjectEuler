/*
Program to find the maximum possible sum from pathing 
through a number triangle.

Note this is a significantly larger version of problem
18 (Max Path Sum 1) which requires reading in a .txt
file containing a triangle with one hundred rows.

Notably, this problem cannot be brute forced like
problem 18 (i.e. checking the sums of all possible
paths).  However, the more elegant sub-triangle
solution from that problem can be used to great
effect.

Therefore, the algorithm used in problem 18 is
also utilized here.  I also implement a basic
file reader to construct the number triangle
from the .txt file which is also placed within
this project directory.

For reference (from problem 18):

Note the following things about the pathing here:
    1) We start at the top of the triangle, and move
    down towards the bottom.  Thus, if we think of this
    triangle as a vector of sub-vectors (with increasing
    length), from a given position in the previous vector,
    we choose a new position in the next vector to path
    through.

    2) Importantly, when pathing, we can only pick from
    the two adjacent numbers to the previous number
    (i.e. diagonally adjacent).  Notice, crucially, that
    for whatever position we are in the previous vector,
    i.e. position i, we can only choose either position
    i or i + 1 in the next vector to continue the path.
    This is a consequence of the triangle sub-vectors
    increasing in size by one element each time.

Therefore, we need to note we are actually solving a system
of problems.
To see this, first note that when we choose a path going down,
we actually need to solve a sub-problem (a sub-triangle,
if you will).  We can keep breaking these problems into parts
until we reach the a corner sub-triangle at the bottom, which
has a trivial solution (i.e. this triangle is a, (b, c), and
clearly the max(b,c) chooses either b or c trivially here).

Therefore, what we actually need to do here is work backwards
towards the top of the triangle by "collapsing" a level of
the triangle by computing all the possible sums going upward
(i.e. compute a + max(b,c) for each element of the row where
a exists).  Note this will modify the elements of the triangle
itself.

We can then continue this going up each level in the triangle
until we reach the top row, which will yield our final sum in
the end.
*/


#include <cstdint>
#include <iostream>
#include <fstream> // For file reading via ifstream.
#include <string>
#include <sstream>
#include <vector>


using lint_t = int_fast16_t;


/* Function to extract a given line into a vector of ints: */
std::vector<lint_t> extractsIntsfromTextLine(const std::string& str)
{
    /* Takes one line into an istream class: */
    std::istringstream stm(str);

    /* Using iterators, convert string to lint_t vector and
    return it: */
    using iterator = std::istream_iterator<lint_t>;

    std::vector<lint_t> seg{ iterator(stm), iterator() };

    return seg;
}


/* Input function to read in a number triangle
from a .txt file: */
std::vector<std::vector<lint_t>> readInputNumTriang(const std::string& filename)
{
    /* Open the .txt file for input: */
    std::ifstream datafile;
    datafile.open(filename);
    

    /* Begin pushing each line as a vector of
    lint_t values: */
    std::string line{};
    std::vector<std::vector<lint_t>> inputTriang{};

    if (datafile.is_open())
    {
        while (getline(datafile, line))
        {
            inputTriang.push_back(extractsIntsfromTextLine(line));
        }
    }


    return inputTriang;
}


int main()
{
	/* Initialize the number triangle by using
    functions to read from the .txt file: */
    std::vector<std::vector<lint_t>> numberTriang{
        readInputNumTriang("p67_NumTriangle.txt") };


    /* Use the sub-triangle algorithm to modify numberTriang
    and calculate the maximum sum.
    Utilizes the std::max() function.for comparison of elements: */
    for (int currentRow{ static_cast<int>(numberTriang.size()) - 2 }; currentRow >= 0; currentRow--)
    {
        for (int currentPos{ 0 }; currentPos <= currentRow; currentPos++)
        {
            /* This is checking the condition of the sub-triangle,
            i.e. replacing the value a with a + max(b,c) for each
            sub-triangle in the overall problem.  Note this is done
            for all a in a given row s.t. we ensure we check all
            existing paths, effectively, without calculating the
            actual total sum of each path. */
            numberTriang.at(currentRow).at(currentPos)
                += std::max(numberTriang.at(currentRow + 1).at(currentPos),
                    numberTriang.at(currentRow + 1).at(currentPos + 1));
        }
    }


    /* Report the final sum to the user: */
    std::cout << "The maximum possible total from pathing through the "
        << "given number triangle was found to be: "
        << numberTriang.at(0).at(0) << ".\n";


	return 0;
}