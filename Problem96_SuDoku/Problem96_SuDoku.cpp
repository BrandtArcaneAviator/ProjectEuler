/*
Program to solve fifty Su Doku puzzles and then
find the sum the 3-digit numbers formed by the 
first three numbers in the top left corner of 
each solution grid.


*/


#include <iostream>
#include <vector>


/* Class for Su Doku matricies: */
class SuDoku
{
private:
    std::vector<std::vector<int>> m_matrix{};



public:
    SuDoku()
    {
        std::vector<int> row(9);

        for (int i{ 0 }; i < 9; ++i)
        {
            m_matrix.push_back(row);
        }
    }

    SuDoku(const std::vector<std::vector<int>>& matrix) : m_matrix{matrix}
    {
    }

    std::vector<std::vector<int>> getMatrix() { return m_matrix; }
    int getMatrixValueAt(const int& row, const int& col) { return getMatrix().at(row).at(col); }

    void setValueInMatrix(const int& val, const int& row, const int& col)
    {
        getMatrix().at(row).at(col) = val;
    }


    bool checkValueAgainstRow(const int& val, const int& row)
    {
        /* Check through all column positions of a row
        for val; if it already exists return false: */
        for (int i{ 0 }; i < 9; ++i)
        {
            if (getMatrix().at(row).at(i) == val)
                return false;
        }

        /* If for loop succeeds, val is not in row,
        so return true: */
        return true;
    }


    bool checkValueAgainstColumn(const int& val, const int& col)
    {
        /* Check through all row positions of a column
        for val; if it already exists return false: */
        for (int i{ 0 }; i < 9; ++i)
        {
            if (getMatrix().at(i).at(col) == val)
                return false;
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
                if (getMatrix().at(i).at(j) == val)
                    return false;
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


    /* Replaces all zero values in SuDoku matrix
    using the conditions of the other member
    functions: */
    void solveMatrix()
    {
        /* For all zeroes in matrix: */
        for (int i{ 0 }; i < 9; ++i)
        {
            for (int j{ 0 }; j < 9; ++j)
            {
                if (getMatrix().at(i).at(j) == 0)
                {
                    /* Run through 1-9 looking for potential
                    solutions: */
                    for (int val1{ 1 }; val1 <= 9; ++val1)
                    {
                        if (checkValAgainstAll(val1, i, j))
                        {
                            setValueInMatrix(val1, i, j);
                            break;
                        }
                    }
                }
            }
        }
    }


};


int main()
{
    /* d */



    return 0;
}