#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
#include <vector>
#include <fstream> // For file reading
#include <ctime>   // For time measurement
#include <chrono>  // For time measurement
#include <omp.h>

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

// First Fit (Parallelized)
int firstFit(int box[], int length, int capacity)
{
    // We have to initialize result (Count of bins)
    int res = 0;
    // We have to create an array to store remaining space in bins there can be maximum n bins
    int *bin_rem = new int[length];

// We have to place elements one by one
#pragma omp parallel for // Parallelize the loop
    for (int i = 0; i < length; i++)
    {
        bool found = false;

        for (int j = 0; j < res && !found; j++)
        {

#pragma omp critical // Ensure that only one thread accesses the bin_rem array at a time
            {
                if (bin_rem[j] >= box[i])
                {
                    bin_rem[j] -= box[i];
                    found = true;
                }
            }
        }

        // If no bin could accommodate box[i]
        if (!found)
        {
            bin_rem[res] = capacity - box[i];
            res++;
        }
    }

    // Testing the bin_rem array
    for (int k = 0; k < res; k++)
        // Leftover space in the bin
        cout << "Bin " << k << ": " << bin_rem[k] << endl;

    return res;
}

// Driver program
int main(int argc, char const *argv[])
{
    // Start measuring time
    auto start = high_resolution_clock::now();

    vector<int> box = readTxtFile();

    // surface area of the Bin capacity = 2(h*l*w)
    int capacity = 2 * (50 * 50 * 100);
    int length = box.size();

    cout << "Number of bins required in First Fit: " << firstFit(box.data(), length, capacity) << endl;

    // Stop measuring time
    auto stop = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nTime in microseconds: " << duration.count() << endl;

    return 0;
}