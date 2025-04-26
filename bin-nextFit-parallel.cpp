#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
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

int nextFit(vector<int> &box, int length, int capacity)
{
    int total_bins = 0;

    #pragma omp parallel
    {
        int local_bins = 0;
        int local_bin_rem = capacity;

        #pragma omp for
        for (int i = 0; i < length; i++)
        {
            if (box[i] > local_bin_rem)
            {
                local_bins++;
                local_bin_rem = capacity - box[i];
            }
            else
            {
                local_bin_rem -= box[i];
            }
        }

        #pragma omp atomic
        total_bins += local_bins;
    }

    return total_bins;
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
    cout << "Number of bins required in First Fit: " << nextFit(box, length, capacity) << endl;

    // Stop measuring time
    double end_time = omp_get_wtime();
    // Calculate the time taken in milliseconds
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    return 0;
}