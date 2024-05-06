#include <iostream>
#include <list>
#include <vector>
using namespace std;

class HashTable {
private:
    list<int>* table;
    int total_elements;
    // Hash function to calculate hash for a value:
    int getHash(int key) {
        return key % total_elements;
    }

public:
    // Constructor to create a hash table with 'n' indices:
    HashTable(int n) {
        total_elements = n;
        table = new list<int>[total_elements];
    }

    // Insert data in the hash table:
    void insertElement(int key) {
        // adds a key into the bucket
        int index = getHash(key);
        table[index].push_back(key);

    }

    // Remove data from the hash table:
    void removeElement(int key) {
        //Removes the key:
        int index = getHash(key);
        table[index].remove(key);

    }

    void printAll() {
        //output:
        for (int i = 0; i < total_elements; ++i) {
            cout << "Index " << i << ": ";
            for (int val : table[i]) {
                cout << val << " => ";
            }
            cout << endl;
        }
    };
};


class HashTable2 {
private:
    //I prefer using vectors, so I'm going to use vectors here, I used a list above because it was already provided. 
    vector<vector<int>> table;
    int total_elements;

    //the two functions to perform the double hashing
    int hash1(int key) {
        return key % total_elements;
    }

    int hash2(int key) {
        return 7 - (key % 7);
    }

public:
    //creating the second hash table
    HashTable2(int n) {
        total_elements = n;
        table.resize(total_elements);
    }

    void insertElement(int key) {
        //if the bucket is empty where the hash should go put it there. 
        int index = hash1(key);
        if (table[index].empty()) {
            table[index].push_back(key);
        }
        //if not, perform the double hash function. 
        else {
            int index2 = hash2(key);
            int i = 1;
            while (true) {
                int newIndex = (index + i * index2) % total_elements;
                if (table[newIndex].empty()) {
                    table[newIndex].push_back(key);
                    break;
                }
                ++i;
            }
        }
    }

    void removeElement(int key) {
        //calculates the first index. 
        int index = hash1(key);
        //check if bucket is empty, if not, erase it from memory so no exceptions are thrown, this is for the first element it checks.
        if (!table[index].empty()) {
            table[index].erase(remove(table[index].begin(), table[index].end(), key), table[index].end());
        }
        //calculates the second hash. 
        int index2 = hash2(key);
        int i = 1;
        //remove the double hashed element. 
        while (true) {
            int newIndex = (index + i * index2) % total_elements;
            if (!table[newIndex].empty()) {
                table[newIndex].erase(remove(table[newIndex].begin(), table[newIndex].end(), key), table[newIndex].end());
                return;
            }
            ++i;
        }
    }
    //output
    void printAll() {
        for (int i = 0; i < total_elements; ++i) {
            cout << "Index " << i << ": ";
            for (int val : table[i]) {
                cout << val;
            }
            cout << endl;
        }
    }
    //destructor
    ~HashTable2() {
    }

};



int main() {

    // Create a hash table with 11 indices:
    HashTable ht(11);
    // Declare the data to be stored in the hash table:
    int arr[] = { 2, 8, 19, 20, 26 };

    // Insert the whole data into the hash table:
    for (int i = 0; i < 5; i++)
        ht.insertElement(arr[i]);

    cout << "..:: Hash Table with separate chaining::.." << endl;
    ht.printAll();

    ht.removeElement(8);
    cout << endl << "..:: After deleting 8 ::.." << endl;
    ht.printAll();
    cout << endl;
    cout << "*************************************************************************" << endl;

    // Create a hash table with 11 indices:
    HashTable2 ht2(11);

    // Declare the data to be stored in the hash table:
    int arr2[] = { 2, 8, 19, 20, 26 };

    // Insert the whole data into the hash table:
    for (int i = 0; i < 5; i++)
        ht2.insertElement(arr2[i]);

    cout << "..:: Hash Table with double hashing::.." << endl;
    ht2.printAll();

    ht2.removeElement(8);
    cout << endl << "..:: After deleting 8 ::.." << endl;
    ht2.printAll();

    return 0;

}
