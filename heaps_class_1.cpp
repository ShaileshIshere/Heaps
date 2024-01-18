#include<bits/stdc++.h>

using namespace std;

struct Heap {
    int *arr, size, capacity;
    Heap(int capacity) : arr(new int[capacity]), capacity(capacity), size(0) {}

    // insertion in heap
    void insertion(int val) {
        // overflow condition
        if(size == capacity) {
            cout << "heap overflow :(" << endl;
            return;
        }
        // increase size
        size++;
        int index = size;
        arr[index] = val;
        // take the val to its correct position
        while(index > 1) {
            int parentIndex = index >> 1;
            if(arr[index] > arr[parentIndex]) {
                swap(arr[index], arr[parentIndex]);
                index = parentIndex;
            }
            else 
                break;
        }
    }

    // deletion in heap
    int deletion() {
        // here we're storing out root node that has to be deleted
        int answer = arr[1];
        // replacing the last node to root node
        arr[1] = arr[size];
        // now delete the last node from the heap
        size--;

        // now heapify and check wether the root node is suitable to become the root node?
        int index = 1;
        while(index < size) {
            int leftIndex = 2 * index;
            int rightIndex = 2 * index + 1;
            // find the greatest value between top 3 nodes
            int largestIndex = index;

            // check if the left node is greatest
            if(leftIndex <= size && arr[leftIndex] > arr[largestIndex])
                largestIndex = leftIndex;

            // check if the right node is greatest
            if(rightIndex <= size && arr[rightIndex] > arr[largestIndex])
                largestIndex = rightIndex;

            // check if the root node is the greatest
            if(index == largestIndex)
                break;
            else {
                swap(arr[index], arr[largestIndex]);
                index = largestIndex;
            }
        }
        return answer;
    }

    void print_heap() {
        cout << "printing heap through array :- " << endl << "[ ";
        for(int i=1; i<=size; ++i)
            cout << arr[i] << " ";
        cout << "]" << endl;
    }
};

// convert a array into heap
// heapification through recursion : TC - O(log n)
void heapify(int *arr, int n, int index) {
    int leftIndex = 2 * index;
    int rightIndex = 2 * index + 1;
    int largestIndex = index;
    // now obtain the maximum digit among the top 3 digits
    if(leftIndex <= n && arr[leftIndex] > arr[largestIndex])
        largestIndex = leftIndex;
    if(rightIndex <= n && arr[rightIndex] > arr[largestIndex])
        largestIndex = rightIndex;
    // after these two conditions the value present in the [largestIndex] is the largest value of all
    if(index != largestIndex) {
        swap(arr[index], arr[largestIndex]);
        // now recursion will handle after this 
        index = largestIndex;
        heapify(arr, n, index);
    }
}
void build_heap(int *arr, int n) {
    for(int index=n/2; index>0; --index) 
        heapify(arr, n, index);
}
void print_heapify(int *arr, int n) {
    cout << "printing heap through array :- " << endl << "[ ";
    for(int i=1; i<=n; ++i)
        cout << arr[i] << " ";
    cout << "]" << endl;
}

// heap sort - TC O(n log(n))
void heap_sort(int *arr, int n) {
    while(n != 1) {
        swap(arr[1], arr[n]);
        --n;
        heapify(arr, n, 1);
    }
}

int main() {

    // int n, x;
    // cout << "enter the size of your array : ";
    // cin >> n;
    // Heap h(n);
    // cout << "enter the array to implement heap :" << endl;
    // for(int i=0; i<h.capacity; ++i) {
    //     cin >> x;
    //     h.insertion(x);
    // }
    // h.print_heap();
    // int deleted_node = h.deletion();
    // cout << "deleted node from the heap is : " << deleted_node << endl;
    // h.print_heap();

    int x;
    cout << "enter the size of array : ";
    cin >> x;
    int *arr = new int[x];
    for(int i=1; i<=x; ++i) 
        cin >> arr[i];
    int n = x;
    build_heap(arr, n);
    print_heapify(arr, n);

    // heap_sort(arr, n);
    // cout << "array after heap sort : " << endl;
    // for(int i=1; i<=n; ++i)
    //     cout << arr[i] << " ";
    // cout << endl;

    return 0;
}