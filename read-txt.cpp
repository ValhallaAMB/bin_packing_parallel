#include <iostream>
#include <string>
#include <fstream> // For file reading
#include <vector>
#include <algorithm> // For sort()

// Allows the use of standard library functions and objects
// without needing to prefix them with std::
using namespace std;

int main(int argc, char const *argv[])
{
    // Create a text string, which is used to output the text file
    string myText;

    // There are 3000 boxes/entries in the text file
    vector<int> weight;

    // Read from the text file
    ifstream MyReadFile("box_sizes.txt");

    // Counter
    int i = 0;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText))
    {
        int product = 1;
        size_t pos = 0;
        while ((pos = myText.find(' ')) != string::npos)
        {
            product *= stoi(myText.substr(0, pos));
            myText.erase(0, pos + 1);
        }
        product *= stoi(myText) * 2; // Multiply the last number

        // Output the text from the file
        weight.push_back(product); // Convert string to int and store in weight vector
        // cout << "Weight[" << i << "] = " << weight.at(i) << endl;
        i++;
    }

    // Close the file
    MyReadFile.close();

    sort(weight.begin(), weight.end(), std::greater<int>());

    for (int i = 0; i < weight.size(); i++)
    {
        cout << "Sorted Weight[" << i << "] = " << weight.at(i) << endl;
    }

    return 0;
}
