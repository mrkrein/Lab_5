#include "p3mat.h"
#include <iostream>
#include <ostream>

void sortMatrixDescending(int** matrix, int rows, int cols)
{
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 3 == 0)
            {
                count++;
            }
        }
    }
    std::cout << "Multiples of three : " << count << std::endl;
}

