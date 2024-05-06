#include <iostream>
#include <vector>
using namespace std;

//function to make into a minimum Heap.
void minHeapify(vector<int>& heap, int i, int heapSize) {
    //to get the left and the right childs of the heap. 
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    //making sure it doesn't go out of the size and finding the smallest:
    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }

    //same thing but for right. 
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }

    //if smallest isn't at i swap and go recursively until you find the smallest at i. 
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, smallest, heapSize);
    }
}

//function to build the minimum heap. 
void buildMinHeap(vector<int>& heap) {
    int heapSize = heap.size();

    //start at the last non leaf node, iterate to root. 
    for (int i = heapSize / 2 - 1; i >= 0; --i) {
        //call minHeap at i to ensure the position in the min heap satisfies with the index i. 
        minHeapify(heap, i, heapSize);
    }
}

// Function to find the k'th largest element in an array using min-heap
int findKthLargest(vector<int> const& ints, int k) {
    vector<int> heap(ints.begin(), ints.begin() + k);
    buildMinHeap(heap);

    //Iterating through the entire vector. 
    for (int i = k; i < ints.size(); ++i) {
        // doing a comparison. if it is bigger then ->
        if (ints[i] > heap[0]) {
            // -> heap at index 0 = ints at i. This sets the kth largest element to heap [0]
            heap[0] = ints[i];
            //build the heap over again. 
            minHeapify(heap, 0, k);
        }
    }

    //return the kth largest. 
    return heap[0];
}

int main() {
    vector<int> ints = { 7, 4, 6, 3, 9, 1 };
    int k = 3;

    cout << "k'th largest array element is " << findKthLargest(ints, k) << endl;

    return 0;
}
