/*
Program to solve fifty Su Doku puzzles and then
find the sum the 3-digit numbers formed by the 
first three numbers in the top left corner of 
each solution grid.


*/


#include <algorithm> // for std::set_difference()
#include <iostream>
#include <vector>


/* Class for Su Doku matricies: */
class SuDoku
{
private:
    /* This is a 3-d tensor because we want each
    cell to hold all possible values for that cell,
    specifically for unknown values: */
    std::vector<std::vector<std::vector<int>>> m_matrix{};


public:
    /* Constructor making a matrix with all
    cells full of potential values: */
    SuDoku()
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
    SuDoku(const std::vector<std::vector<int>>& matrix) : m_matrix{matrix}
    {
        for (int k{0}; k < 9; ++k)
        {
            for (int j{ 0 }; j < 9; ++j)
            {
                // For zero values: 
                if (getMatrix().at(k).at(j).at(0) == 0)
                {
                    // Replace with potential values:
                    getMatrix().at(k).at(j) = { 1,2,3,4,5,6,7,8,9 };
                }
            }
        }
    }

    std::vector<std::vector<std::vector<int>>> getMatrix() { return m_matrix; }

    /* Note this fixes the possible values of the cell to one
    given value (i.e. a vector of one int is now the cell).
    Only meant to be used for val = 1 through 9. */
    void setValueInMatrix(const int& val, const int& row, const int& col)
    {
        getMatrix().at(row).at(col) = { val };
    }


    bool checkValueAgainstRow(const int& val, const int& row)
    {
        /* Check through all "filled" column positions of a row
        for val; if it already exists return false: */
        for (int i{ 0 }; i < 9; ++i)
        {
            if (getMatrix().at(row).at(i).size() == 1)
            {
                if (getMatrix().at(row).at(i).at(0) == val)
                    return false;
            }
        }

        /* If for loop succeeds, val is not in row,
        so return true: */
        return true;
    }


    bool checkValueAgainstColumn(const int& val, const int& col)
    {
        /* Check through all "filled" row positions of a column
        for val; if it already exists return false: */
        for (int i{ 0 }; i < 9; ++i)
        {
            if (getMatrix().at(i).at(col).size() == 1)
            {
                if (getMatrix().at(i).at(col).at(0) == val)
                    return false;
            }
        }

        /* If for loop succeeds, val is not in column,
        so return true: */
        return true;
    }


    bool checkValueAgainstBox(const int& val, const int& row, const int& col)
    {
        int rowleftbound{};
        int rowrightbound{};
        int colupbound{};
        int colbotbound{};
        
        /* First, determine the box we are in using
        switch statements: */
        switch (row)
        {
        case 0: // Note the fallthrough of cases here.
        case 1:
        case 2: rowleftbound = 0; rowrightbound = 2; break;
        case 3:
        case 4:
        case 5: rowleftbound = 3; rowrightbound = 5; break;
        case 6:
        case 7:
        case 8: rowleftbound = 6; rowrightbound = 8; break;
        }

        switch (col)
        {
        case 0:
        case 1:
        case 2: colupbound = 0; colbotbound = 2; break;
        case 3:
        case 4:
        case 5: colupbound = 3; colbotbound = 5; break;
        case 6:
        case 7:
        case 8: colupbound = 6; colbotbound = 8; break;
        }

        for (int i{ rowleftbound }; i <= rowrightbound; ++i)
        {
            for (int j{ colupbound }; j <= colbotbound; ++j)
            {
                if (getMatrix().at(i).at(j).size() == 1)
                {
                    if (getMatrix().at(i).at(j).at(0) == val)
                        return false;
                }
            }
        }

        return true;
    }


    bool checkValAgainstAll(const int& val, const int& row, const int& col)
    {
        if (checkValueAgainstRow(val, row) && checkValueAgainstColumn(val, col)
            && checkValueAgainstBox(val, row, col))
        {
            return true;
        }
        else
        {
            return false;
        }
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
            /* Checking 1-9 for the given cell: */
            for (int a{ 1 }; a <= 9; ++a)
            {
                /* If any of these return false, then the given a for
                the cell defined by row, col cannot have that value: */
                if (!checkValAgainstAll(a,row,col))
                {
                    /* So remove a from that cell: */
                    for (int b{ 0 }; b < static_cast<int>(getMatrix().at(row).at(col).size()); ++b)
                    {
                        if (getMatrix().at(row).at(col).at(b) == a)
                        {
                            /* Removes element from cell vector equal
                            to a; note we can break the inner loop
                            thereafter since the value has been handled. */
                            getMatrix().at(row).at(col).erase(getMatrix().at(row).at(col).begin() + b);
                            break;
                        }
                    }
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
        for (int k{ 0 }; k < 9; ++k)
        {
            for (int j{ 0 }; j < 9; ++j)
            {
                reducePotentialCell(k, j);
            }
        }
    }


    /* Function examining "empty" cells in a given
    row and replacing unique values in that row.
    Reduces the remaining cells thereafter: */
    void solveRowOnce(const int& row)
    {
        std::vector<std::vector<int>> cellCompar{};
        std::vector<int> cellPos{};
        std::vector<int> cellConcat{0};
        

        /* Check column elements in row: */
        for (int j{0}; j < 9; ++j)
        {
            /* Get "empty" cells: */
            if (getMatrix().at(row).at(j).size() > 1)
            {
                cellCompar.push_back(getMatrix().at(row).at(j));
                cellPos.push_back(j);
                if (cellCompar.size() == 1)
                {
                    cellConcat = cellCompar.at(0);
                }
                else
                {
                    cellConcat.insert(cellConcat.end(), getMatrix().at(row).at(j).begin(), 
                        getMatrix().at(row).at(j).end());
                }
            }
        }
        
        /* Now compare the empty cells of that row for unique
        values (i.e. see if any one cell can take a value
        no other can).  By erasing non-distinct values,
        we should get the most distinct value in the row: */
        std::sort(cellConcat.begin(), cellConcat.end());
        cellConcat.erase(std::unique(cellConcat.begin(), cellConcat.end()), cellConcat.end());

        /* ??? */
    }
};


int main()
{
    /* d */



    return 0;
}