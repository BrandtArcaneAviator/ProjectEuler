/*
Program to identify the sum of a path through a triangle
of numbers which yields the maximum value for a given
triangle of numbers.

For example, consider:
        3
       7 4
      2 4 6
     8 5 9 3
The path yielding the maximum sum is then (starting at
the top): 3 -> 7 -> 4 -> 9.

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
#include <vector>


using lint_t = int_fast16_t;


int main()
{
    /* DEBUG: check a smaller triangle: */
    /*std::vector<std::vector<lint_t>> numberTriang{
        {3},
        {7,4},
        {2,4,6},
        {8,5,9,3}
    }; */


    /* Initialize the number triangle being examined here: */
    std::vector<std::vector<lint_t>> numberTriang{
        {75},
        {95,64},
        {17,47,82},
        {18,35,87,10},
        {20,4,82,47,65},
        {19,1,23,75,3,34},
        {88,2,77,73,07,63,67},
        {99,65,4,28,6,16,70,92},
        {41,41,26,56,83,40,80,70,33},
        {41,48,72,33,47,32,37,16,94,25},
        {53,71,44,65,25,43,91,52,97,51,14},
        {70,11,33,28,77,73,17,78,39,68,17,57},
        {91,71,52,38,17,14,91,43,58,50,27,29,48},
        {63,66,4,68,89,53,67,30,73,16,69,87,40,31},
        {4,62,98,27,23,9,70,98,73,93,38,53,60,4,23} 
    };


    /* Use the sub-triangle algorithm to modify numberTriang 
    and calculate the maximum sum.
    Utilizes the std::max() function.for comparison of elements: */
    for (int currentRow{ static_cast<int>(numberTriang.size()) - 2 }; currentRow >= 0; --currentRow)
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