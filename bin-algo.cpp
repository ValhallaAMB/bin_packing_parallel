#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
#include <vector>
#include <fstream> // For file reading
#include <ctime>   // For time measurement
#include <chrono>  // For time measurement

using namespace std;
using namespace chrono;

vector<int> readTxtFile()
{
    // Create a text string, which is used to output the text file
    string extractedText;

    // There are 3000 boxes/entries in the text file
    vector<int> box;

    // Read from the text file
    ifstream readFile("box_sizes.txt");

    // Counter
    int i = 0;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(readFile, extractedText))
    {
        int product = 1;
        size_t pos = 0;

        while ((pos = extractedText.find(' ')) != string::npos)
        {
            // stoi = Converts string to int
            product *= stoi(extractedText.substr(0, pos));
            extractedText.erase(0, pos + 1);
        }
        product *= stoi(extractedText) * 2; // Multiply the last number

        // Output the text from the file
        box.push_back(product); // Store in box vector

        // cout << "box" << i << "] = " << box.at(i) << endl;
        i++;
    }

    // Close the file
    readFile.close();
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
