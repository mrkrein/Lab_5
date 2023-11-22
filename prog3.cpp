#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "p3ar.h"
#include "p3mat.h"
#include <windows.h>
#include <stdio.h>

const int ARRAY_SIZE = 67;
const int MATRIX_ROWS = 5;
const int MATRIX_COLS = 7;

void LoadRun(const char* const s, int* arr, int** matrix, int choice)
{
    void* lib;

    lib = LoadLibrary(s); 

    if (!lib)
    {
        printf("Cannot open library '%s'\n", s);
        return;
    }

    if (choice == 1) {
        void (*sortArr)(int*, int) = (void (*)(int*, int))GetProcAddress((HINSTANCE)lib, "sortArrayDescending");

        if (sortArr == NULL)
        {
            printf("Cannot load function sortArrayDescending from '%s'\n", s);
        }
        else
        {
            sortArr(arr, ARRAY_SIZE); // Call the sortArrayDescending function
        }
    }
    else if (choice == 2) {
        void (*sortMat)(int**, int, int) = (void (*)(int**, int, int))GetProcAddress((HINSTANCE)lib, "sortMatrixDescending");

        if (sortMat == NULL)
        {
            printf("Cannot load function sortMatrixDescending from '%s'\n", s);
        }
        else
        {
            sortMat(matrix, MATRIX_ROWS, MATRIX_COLS); // Call the sortMatrixDescending function
        }
    }
    else {
        printf("Invalid choice.\n");
    }

    FreeLibrary((HINSTANCE)lib); // Unload the library
}

void fillArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 101 - 50;
    }
}

void fillMatrix(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 101 - 50;
        }
    }
}

void printArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printMatrix(int** matrix, int rows, int cols)
{
    int max_width = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int element_width = std::to_string(matrix[i][j]).length();
            if (element_width > max_width)
            {
                max_width = element_width;
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(max_width) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    srand(time(0));
    int* arr = new int[ARRAY_SIZE];
    int** matrix = new int* [MATRIX_ROWS];
    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        matrix[i] = new int[MATRIX_COLS];
    }

    fillArray(arr, ARRAY_SIZE);
    fillMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);

    int choice;
    while (true)
    {
        std::cout << "Select what you want to work with:" << std::endl;
        std::cout << "1. Array " << std::endl;
        std::cout << "2. Matrix" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> choice;
        if (choice < 1 || choice > 3)
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        else
        {
            switch (choice)
            {
            case 1:
            {
                std::cout << "Original array:" << std::endl;
                printArray(arr, ARRAY_SIZE);

                LoadRun("ar.dll", arr, matrix, choice);
            }
            break;
            case 2:
            {
                std::cout << "Original matrix:" << std::endl;
                printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);

                LoadRun("mat.dll", arr, matrix, choice);
            }
            break;
            case 3:
                std::cout << "Exiting the program." << std::endl;
                delete[] arr;
                for (int i = 0; i < MATRIX_ROWS; i++)
                {
                    delete[] matrix[i];
                }
                delete[] matrix;
                return 0;
            }
        }
    }
    delete[] arr;
    for (int i = 0; i < MATRIX_ROWS; i++) 
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}