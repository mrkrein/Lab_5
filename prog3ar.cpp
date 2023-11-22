#include "p3ar.h"
#include <ostream>
#include <iostream>

extern "C" __declspec(dllexport) void sortArrayDescending(int* arr, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 3 == 0) {
            count++;
        }
    }
    std::cout << "Multiples of three : " << count <<std::endl;
}