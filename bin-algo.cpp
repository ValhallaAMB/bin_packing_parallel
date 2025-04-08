#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
#include <vector>
#include <fstream> // For file reading  

using namespace std;
/* We copy firstFit() from above */
int firstFit(int weight1[], int m, int C)
{
    // We have to initialize result (Count of bins)
    int res = 0;
    // We have to create an array to store remaining space in bins there can be maximum n bins
    int *bin_rem = new int[m];
    // We have to place elements one by one
    for (int i = 0; i < m; i++)
    {
        // We have to find the first bin that can accommodate weight1[i]
        int j;
        for (j = 0; j < res; j++)
        {
            if (bin_rem[j] >= weight1[i])
            {
                bin_rem[j] = bin_rem[j] - weight1[i];
                break;
            }
        }
        // If no bin could accommodate weight1[i]
        if (j == res)
        {
            bin_rem[res] = C - weight1[i];
            res++;
        }
    }
    delete[] bin_rem;
    return res;
}
// We have to returns number of bins required implementing first fit decreasing offline algorithm
int firstFitDec(int weight1[], int m, int C)
{
    // At first we sort all weights in decreasing order
    sort(weight1, weight1 + m, std::greater<int>());
    // Now we call first fit for sorted items
    return firstFit(weight1, m, C);
}
// Driver program
int main()
{
    int weight1[] = {2, 5, 4, 7, 8};
    int C = 10;
    int m = sizeof(weight1) / sizeof(weight1[0]);
    cout << "Number of bins required in First Fit "
         << "Decreasing : " << firstFitDec(weight1, m, C);
    return 0;
}
