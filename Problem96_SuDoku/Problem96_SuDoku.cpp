/*
Program to solve fifty Su Doku puzzles and then
find the sum the 3-digit numbers formed by the 
first three numbers in the top left corner of 
each solution grid.  These fifty puzzles are
provided in a separate .txt file, which
will be imported in main() here.

I implement a fairly complex class for this
problem, comprised of a NxNxN tensor matrix
(this is a vector<vector<vector<int>>>).
This is 3-d, not 2-d, so that the matrix's
"empty" cells (those intialized with zero)
can be replaced with cell vectors (the
innermost vector<int>) to hold possible
values.  

Using a reduction member function that
checks the conditions of a given possible
value (between 1 and N) within an "empty"
cell vector against other cell values that
have been "filled" (i.e. were non-zero to
start with and contain only one value in their
cell vector), we can then reduce the "empty"
cell vectors down to more specific possible values,
which improves the sub-sequent solving methodology.
Note the conditions I mention are the rules for
Su Doku:
    i) A given value (1-N) can appear only once
    in a given row.
    ii) A given value (1-N) can appear only once
    in a given column.
    iii) A given value (1-N) can appear only once
    in a given 3x3 sub-matrix.  The overall NxN
    has multiple such 3x3 sub-matricies as
    a result; also note this program is intended
    for 9x9 matrices but COULD be used for N
    larger or smaller than 9 but at current
    this sub-matrix size is fixed at three!

From this reduced tensor (implemented before we 
solve the puzzle), I then implement a recursive
function to solve the puzzle via a backtracking
algorithm.  That is: 

    1) I start at the first cell (row,col) = (0,0) and 
    find the first "empty" cell (i.e. one which has 
    vector.size() > 1 is "empty"), going through columns
    first and wrapping rows when necessary.

    2) For the given "empty" cell, I assume a value from 
    its possible values (note that I save ALL these possible 
    values each time I do this as to not lose information when 
    backtracking).  
    Note this assumed value is picked from the reduced set of 
    values for that "empty" cell and that cell is now considered "filled"
    unless we backtrack to that cell to replace it with another
    value.  
    Also, I MUST check each time I do this (using the 
    conditions above) for new conflicts with any value I assume 
    for another other "empty" cell so that no cell in the same 
    row, column, or 3x3 submatrix takes the same value as the 
    one just assumed. 
    
    3) Then I move to the next cell (going through every 
    column of a row and then wrapping around to the next row) 
    and repeat 2) until either a) the puzzle is fully solved
    or b) no valid value can be assumed in a given "empty" cell.
    
    4) If b) in 3) occurs, then we must backtrack a cell to the
    previous "empty" cell and choose another potential value for
    the assumption in 2). Thus, we backtrack to a previous 2) for
    the previous assumed value to be replaced by another value
    in its reduced cell vector, hence why we save these values
    at 2).  This is done via the recursive nature of the solution
    function; basically we simply pop back the function call stack 
    to the last "empty" cell where we are still holding the possible 
    values of that cell.  We then, again, continue to 3) again
    as normal.  This backtracking process will repeat as many times
    as necessary to fully and correctly solve the whole NxN matrix.

Finally, once a matrix is solved, we take the first three upper-left
corner digits as a 3-digit number to be summed with a sum variable.

Thus, in main, the algorithm for solving all puzzles becomes:
    A) Import the puzzles from the .txt file and save them in
    a vector of SuDoku objects.

    B) Reduce and solve each puzzle using the methodology above
    by using the SuDokuNxN::reduceMatrix() and 
    SuDokuNxN::solveSudokuNxN(0,0) member function calls.

    C) Once all puzzles are solved, use the 
    SuDokuNxN::getFirst3digNum() member function call in a
    for loop over the SuDoku objects in the SuDoku vector
    to sum the first 3 digits of each solved puzzle.

    D) Return the final sum value to the user.


EDIT: At current, this program solves the test
example presented by the problem, but not all the
puzzles in the .txt file.  I need to implement
a read .txt file (non-member!) function to
pull all the puzzles from the .txt file and implement
the for loop over the vector of these puzzles still,
but the basic SuDoku solver works as intended at current.
*/


#include <algorithm> // for std::find()
#include <iostream>
#include <numeric> // for std::iota()
#include <vector>


using lint_t = int_fast16_t;


/* Class for Su Doku matricies: */
class SuDukoNxN
{
private:
    /* This is a 3-d tensor because we want each
    cell to hold all possible values for that cell,
    specifically for unknown values: */
    std::vector<std::vector<std::vector<int>>> m_matrix{};
    int m_n{};


public:
    /* Constructor making a matrix with all
    cells full of potential values, assuming
    9x9 grid: */
    SuDukoNxN() : m_n{ 9 }
    {
        std::vector<int> cell(9);
        for (int i{ 1 }; i <= 9; ++i)
        {
            cell.at(i - 1) = i;
        }

        std::vector<std::vector<int>> row{};

        for (int j{ 0 }; j < 9; ++j)
        {
            row.push_back(cell);
        }

        for (int k{ 0 }; k < 9; ++k)
        {
            m_matrix.push_back(row);
        }
    }

    /* Used to import an existing matrix and
    convert it's zero values to potential values
    (i.e. cells with all possible values, 1-9).
    Note the implicit conversion of a 2-d matrix
    to a 3-d tensor (i.e. each "cell" has a vector
    of one int value, e.g. {1}). */
    SuDukoNxN(const int& n, const std::vector<std::vector<int>>& matrix) : m_n{n}
    {
        std::vector<int> cell{ 0 };
        std::vector<std::vector<int>> row{};

        for (int j{ 0 }; j < n; ++j)
        {
            row.push_back(cell);
        }

        for (int k{ 0 }; k < n; ++k)
        {
            m_matrix.push_back(row);
        }

        /* Makes a cell vector with potential values: */
        std::vector<int> tempcell(n);
        std::iota(tempcell.begin(), tempcell.end(), 1);

        for (int k{0}; k < n; ++k)
        {
            for (int j{ 0 }; j < n; ++j)
            {
                m_matrix.at(k).at(j) = { matrix.at(k).at(j) };

                // For zero values: 
                if (m_matrix.at(k).at(j).at(0) == 0)
                {
                    // Replace with potential values:
                    m_matrix.at(k).at(j) = tempcell;
                }
            }
        }
    }


    /* I'll note this implementation is
    technically unnecessary because referencing
    m_matrix makes it public, effectively, but
    I keep it here for posterity (and nothing else). */
    std::vector<std::vector<std::vector<int>>>& getMatrix() { return m_matrix; }
    int getN() { return m_n; }


    /* Function to print out a given Sudoku matrix: */
    void printSuDokuMatrix()
    {
        for (int k{0}; k < getN(); ++k)
        {
            for (int j{0}; j < getN(); ++j)
            {
                for (int i{0}; i < static_cast<int>(getMatrix().at(k).at(j).size()); ++i)
                {
                    std::cout << getMatrix().at(k).at(j).at(i);
                }
                std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }


    /* Member function that checks a given value of
    a cell against other cells in its row, its column,
    and its 3x3 submatrix: */
    bool checkValAgainstAll(const int& val, const int& row, const int& col)
    {
        /* Check through all "filled" column positions of a row
        for val; if it already exists return false: */
        for (int i{ 0 }; i < getN(); ++i)
        {
            /* Cataches only "filled" cells: */
            if (getMatrix().at(row).at(i).size() == 1)
            {
                if (getMatrix().at(row).at(i).at(0) == val)
                    return false;
            }
        }


        /* Check through all "filled" row positions of a column
        for val; if it already exists return false: */
        for (int j{ 0 }; j < getN(); ++j)
        {
            /* Catches "filled" cells: */
            if (getMatrix().at(j).at(col).size() == 1)
            {
                if (getMatrix().at(j).at(col).at(0) == val)
                    return false;
            }
        }
        

        /* Check val against the 3x3 box the chosen cell
        (row,col) is in: */
            /* Associates rows 0,1,2 , 3,4,5 , and 6,7,8
            together; same for columsns: */
        int startRow{row - (row % 3)};
        int startCol{col - (col % 3)};

        for (int k{ 0 }; k < 3; ++k)
        {
            for (int a{ 0 }; a < 3; ++a)
            {
                /* Catch "filled" cells only: */
                if (getMatrix().at(startRow + k).at(startCol + a).size() == 1)
                {
                    if (getMatrix().at(startRow + k).at(startCol + a).at(0) == val)
                        return false;
                }
            }
        }


        /* If we've reached this point, then no
        conflicts are found and we return that
        val is a valid solution to the cell (row,col): */
        return true;
    }


    /* Member function to remove possible values
    of "empty" (zero initially) cells by comparing
    to "filled" values: */
    void reducePotentialCell(const int& row, const int& col)
    {
        /* Checks that the cell we are accessing is not
        a "filled" cell. */
        if (getMatrix().at(row).at(col).size() > 1)
        {
            std::vector<int> temp{};

            /* Checking 1-9 for the given cell: */
            for (int a{ 1 }; a <= getN(); ++a)
            {
                /* If any of these return false, then the given a for
                the cell defined by row, col cannot have that value: */
                if (!checkValAgainstAll(a, row, col))
                {
                    /* So remove a from that cell using
                    erase-remove idiom (NOTE this means
                    we MUST copy the cell to a temp one
                    to prevent iterator invalidation): */    
                    temp = getMatrix().at(row).at(col);
                    temp.erase(std::remove(temp.begin(), temp.end(), a), temp.end());
                    getMatrix().at(row).at(col) = temp;
                }
            }
        }
    }


    /* Reduces every "empty" cell in the
    matrix, removing possible values present
    in other "filled" cells: */
    void reduceMatrix()
    {
        /* Look through cells in matrix for
        "empty" cells (i.e. the zeroes that are
        now possible value cell vectors)
        and reduce the possible values using
        reducePotentialCell(): */
        for (int k{ 0 }; k < getN(); ++k)
        {
            for (int j{ 0 }; j < getN(); ++j)
            {
                reducePotentialCell(k, j);
            }
        }
    }


    /* Recursive member function to solve a SuDoku matrix.
    Note that we DO actually modify input paramaeters
    row, col during the recursion!  When called in main,
    use solveSudokUNxN(0,0) (i.e. start at first cell). 
    Also ensure that the matrix has already been reduced
    once before calling this function. */
    bool solveSuDukoNxN(int row, int col)
    {
        /* First, check that we are not at
        the end of the matrix (i.e. row 8,
        col pos 9 (i.e. getMatirx.at(8).end()
        which is one cell past the final cell): */
        if (row == ( getN()- 1) && col == getN())
        {
            return true; //i.e. we've reached the end of the matrix
        }


        /* Note if col becomes 9 we'll fall out of the
        access of the matrix, so we ensure it instead
        wraps around to next row, first col: */
        if (col == getN())
        {
            row++;
            col = 0;
        }


        /* First instance of recursion, where if
        we find that current cell already contains a
        value (i.e. is "filled" as above), then move
        to next cell).  This guarantees that any
        code past this line is only for "empty" cells! */
        if (getMatrix().at(row).at(col).size() == 1)
            return solveSuDukoNxN(row, col + 1);


        /* Now to run the backtracking algorithm on
        "empty" cells. Since matrix is already reduced,
        the possible values of a given cell are 
        contained in that cell.  Thus, we pick values
        only from the given cell (row,col) here: */
        std::vector<int> tempCell{getMatrix().at(row).at(col)};
        for (int val1 : tempCell)
        {
            /* Note it is necessary once values
            are assigned to "empty" cells that we
            ensure no other "empty" cell tries to
            take the same value, hence this if
            statement.  We do not use the reduce
            function here because that would completely
            erase the potential values! */
            if (checkValAgainstAll(val1, row, col))
            {
                /* Now, we assume a given value for
                the cell (row, col) and recurse to the next
                cell: */
                getMatrix().at(row).at(col) = { val1 };

                if (solveSuDukoNxN(row, col + 1))
                    return true;
            }

            /* Now, if the full solution fails for
            the choice of (row,col)'s value we
            just made (i.e. somewhere in the
            recursion the if statement above fails),
            then reset the choice back to its possible
            values (i.e. why we save tempCell): */
            getMatrix().at(row).at(col) = tempCell;
        }

        
        /* If we hit this point, it's because there
        are no valid solutions at the current point
        of the recursion where any of the values
        in the cell (row,col) are valid.  Therefore,
        this solution must fail and return false: */
        return false;
    }


    /* Member function returning the first three
    cells (0,0), (0,1), (0,2) as a 3-digit number: */
    lint_t getFirst3digNum()
    {
        return ( (getMatrix().at(0).at(0).at(0) * 100)
            + (getMatrix().at(0).at(1).at(0) * 10)
            + getMatrix().at(0).at(2).at(0) );
    }
};


int main()
{
    /* Initialize sum variable: */
    lint_t finalSum{ 0 };

    /* DEBUG: Example SuDoku Matrix: */
    const int n{ 9 };
    SuDukoNxN testcase(n, {
        { 0,0,3,0,2,0,6,0,0 },
        { 9,0,0,3,0,5,0,0,1 },
        { 0,0,1,8,0,6,4,0,0 },
        { 0,0,8,1,0,2,9,0,0 },
        { 7,0,0,0,0,0,0,0,8 },
        { 0,0,6,7,0,8,2,0,0 },
        { 0,0,2,6,0,9,5,0,0 },
        { 8,0,0,2,0,3,0,0,9 },
        { 0,0,5,0,1,0,3,0,0 } });

    testcase.reduceMatrix();

    /* DEBUG: check the reduced matrix: */
    /*testcase.printSuDokuMatrix(); */

    if (testcase.solveSuDukoNxN(0, 0))
    {
        testcase.printSuDokuMatrix();
        finalSum += testcase.getFirst3digNum();
        std::cout << finalSum << "\n";
    }
    else
    {
        std::cout << "No valid SuDoku solution was found.\n";
    }

    return 0;
}