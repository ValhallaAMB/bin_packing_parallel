#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
#include <vector>
#include <fstream> // For file reading
#include <ctime>   // For time measurement
#include <chrono>  // For time measurement
#include <sstream> // For istringstream

using namespace std;
using namespace chrono;

vector<int> readTxtFile()
{
    string extractedText;               // Create a text string, which is used to output the text file
    vector<int> box;                    // There are 3000 boxes/entries in the text file
    ifstream readFile("box_sizes.txt"); // Read from the text file

    // Check if the file opened successfully
    while (getline(readFile, extractedText))
    {
        int l, w, h;
        // Use istringstream to extract integers from the string
        istringstream iss(extractedText);

        // Read the three integers from the string
        if (iss >> l >> w >> h)
        {
            int product = l * w * h * 2;
            box.push_back(product); // Calculate the surface area of the box and add it to the vector
        }
    }

    readFile.close(); // Close the file
    return box;
}

/*
// Next Fit (Sequential)
int nextFit(vector<int> &box, int length, int capacity)
{
    // Result (Count of bins) and remaining capacity in current bin are initialized.
    int res = 0, bin_rem = capacity;

    // We have to place elements one by one
    for (int i = 0; i < length; i++)
    {
        // If this element can't fit in current bin
        if (box[i] > bin_rem)
        {
            res++; // Use a new bin
            bin_rem = capacity - box[i];
        }
        else
            bin_rem -= box[i];
    }

    for (int k = 0; k < res; k++)
    {
        // Leftover space in the bin
        cout << "Bin " << k << ": " << bin_rem << endl;
    }
    return res;
}
*/

// First Fit (Sequential)
int firstFit(int weight1[], int length, int C)
{
    // We have to initialize result (Count of bins)
    int res = 0;
    // We have to create an array to store remaining space in bins there can be maximum n bins
    int *bin_rem = new int[length];

    // We have to place elements one by one
    for (int i = 0; i < length; i++)
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

    // Testing the bin_rem array
    for (int k = 0; k < res; k++)
    {
        // Leftover space in the bin
        cout <<  bin_rem[k] << endl;
        // "Bin " << k << ": " <<
    }

    return res;
}

/*
// First Fit Decreasing (Sequential)
int firstFit(vector<int> &box, int length, int capacity)
{
    // We have to initialize result (Count of bins)
    int res = 0;
    // We have to create an array to store remaining space in bins there can be maximum n bins
    // bin_ren = remaining space in bin
    int *bin_rem = new int[length];
    // We have to place elements one by one
    // We have to find the first bin that can accommodate box[i]
    int j;
    for (int i = 0; i < length; i++)
    {
        for (j = 0; j < res; j++)
        {
            if (bin_rem[j] >= box[i])
            {
                bin_rem[j] = bin_rem[j] - box[i];
                break;
            }
        }
        // If no bin could accommodate box[i]
        if (j == res)
        {
            bin_rem[res] = capacity - box[i];
            res++;
        }
    }
    // Testing the bin_rem array
    for (int k = 0; k < res; k++)
    {
        // Leftover space in the bin
        cout << "Bin " << k << ": " << bin_rem[k] << endl;
    }

    delete[] bin_rem;

    return res;
}

// We have to returns number of bins required implementing first fit decreasing offline algorithm
int firstFitDec(vector<int> &box, int length, int C)
{
    // At first we sort all weights in decreasing order
    sort(box.begin(), box.end(), std::greater<int>());

    // Now we call first fit for sorted items
    return firstFit(box, length, C);
}
*/

// Driver program
int main(int argc, char const *argv[])
{
    // Start measuring time
    auto start = high_resolution_clock::now();

    vector<int> box = readTxtFile();

    // surface area of the Bin capacity = 2(h*l*w)
    int capacity = 2 * (50 * 50 * 100);
    int length = box.size();

    // First Fit Decreasing (Sequential)
    // cout << "Number of bins required in First Fit Decreasing: " << firstFitDec(box, length, capacity) << endl;

    // Next Fit (Sequential)
    // cout << "Number of bins required in Next Fit: " << nextFit(box, length, capacity) << endl;

    // First Fit (Sequential)
    cout << "Number of bins required in First Fit: " << firstFit(box.data(), length, capacity) << endl;

    // Stop measuring time
    auto stop = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nTime in microseconds: " << duration.count() << endl;

    return 0;
}
