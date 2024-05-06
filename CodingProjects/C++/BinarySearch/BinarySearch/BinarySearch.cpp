/*Logan Coffey
This program is a basic binary search algorithm.
It takes an input of a sorted vector list and takes the middle element to split the sides by two (based off of greater than and less than)
It then takes the middle element recursively and compares it to the searched for number until found. 
*/ 

#include <iostream>
#include <vector>

using namespace std;

int BinarySearch(vector<int> searchThrough, int check) {
    //Case where element is never found, however with my input handling in int main() this should never happen. 
    if (searchThrough.empty()) {
        return -1; // Element not found
    }

    //Getting the middle index everytime.
    int middleIndex = searchThrough.size() / 2;
    int middle = searchThrough.at(middleIndex);

    //Found the element.
    if (middle == check) {
        return middle; // Element found
    }
    
    //Recursive calls until the element is never found. 
    else if (middle < check) {
        vector<int> newVect(searchThrough.begin() + middleIndex + 1, searchThrough.end());
        return BinarySearch(newVect, check);
    }
    else {
        vector<int> newVect(searchThrough.begin(), searchThrough.begin() + middleIndex);
        return BinarySearch(newVect, check);
    }
}

int main() {
    int input, result;
    cout << "Pick a number, 1 - 100\n";
    cin >> input;

    //Ensuring number is within range.
    while (input > 100 || input <= 0) {
        cout << "Please pick a number within the range of 1 to 100.\n";
        cin >> input;
    }

    //Creating a vector 1-100.
    vector<int> sortedVector(100);
    for (int i = 0; i < sortedVector.size(); i++) {
        sortedVector[i] = i + 1;
    }

    //Results and output:
    result = BinarySearch(sortedVector, input);

    if (result != -1) {
        cout << result << " was found in the list of numbers" << endl;
    }
    else {
        cout << "Element not found" << endl;
    }

    return 0;
}
