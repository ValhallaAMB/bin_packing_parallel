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
    auto start = high_resolution_clock::now();

    vector<int> box = readTxtFile();

    // surface area of the Bin capacity = 2(h*l*w)
    int capacity = 2 * (50 * 50 * 100);
    int length = box.size();

    cout << "Number of bins required in Next Fit: " << nextFit(box, length, capacity) << endl;

    // Stop measuring time
    auto stop = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nTime in microseconds: " << duration.count() << endl;

    return 0;
}