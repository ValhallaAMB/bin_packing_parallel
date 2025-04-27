#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream> // For file reading
#include <sstream> // For istringstream
#include <omp.h>

using namespace std;

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

    /*
    // Testing the bin_rem array
    for (int k = 0; k < res; k++)
        // Leftover space in the bin
        cout << "Bin " << k << ": " << bin_rem[k] << endl;
    */

    return res;
}

// Driver program
int main(int argc, char const *argv[])
{
    // Start measuring time
    double start_time = omp_get_wtime();

    // Read the box sizes from the text file using the readTxtFile function
    vector<int> box = readTxtFile();

    // surface area of the Bin capacity = 2(h*l*w)
    int capacity = 2 * (50 * 50 * 100);
    int length = box.size();

    // Perform First Fit algorithm
    cout << "Number of bins required in First Fit: " << firstFit(box.data(), length, capacity) << endl;

    // Stop measuring time
    double end_time = omp_get_wtime();
    // Calculate the time taken in milliseconds
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    return 0;
}