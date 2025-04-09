#include <iostream>
#include <stdio.h>
#include <algorithm> // For sort()
#include <string>
#include <vector>
#include <fstream> // For file reading

using namespace std;

/* We copy firstFit() from above */
int firstFit(vector<int> &box, int length, int capacity)
{
    // We have to initialize result (Count of bins)
    int res = 0;
    // We have to create an array to store remaining space in bins there can be maximum n bins
    // bin_ren = remaining space in bin
    int *bin_rem = new int[length];
    // We have to place elements one by one
    for (int i = 0; i < length; i++)
    {
        // We have to find the first bin that can accommodate box[i]
        int j;
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

// Driver program
int main(int argc, char const *argv[])
{
    vector<int> box = readTxtFile();
    int capacity = 2 * (50 * 50 * 100); // surface area of the Bin capacity = 2(h*l*w)
    int length = box.size();

    cout << "Number of bins required in First Fit Decreasing: " << firstFitDec(box, length, capacity) << endl;

    return 0;
}
