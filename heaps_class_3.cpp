#include<bits/stdc++.h>

using namespace std;

// merge [k] no. of sorted arrays of same size into a single sorted array
struct heap {
    int data, rowIndex, colIndex;
    heap(int val, int row_val, int col_val) : data(val), rowIndex(row_val), colIndex(col_val) {}
};
struct custom_comp {
    bool operator()(heap* data_1, heap* data_2) {
        return data_1->data > data_2->data;
    }
};
void merege_k_sorted_arrays(vector<int> &ans, int rows, int cols, vector<vector<int>> &given_arrays) {
    priority_queue<heap*, vector<heap*>, custom_comp> pq;
    /*process first elements of k no. of arrays
    here temp = first element of each array*/
    for(int i=0; i<rows; ++i) {
        heap* temp = new heap(given_arrays[i][0], i, 0);
        pq.push(temp);
    }
    /*here we're fetching the smallest element from the [k] arrays and inserting into [ans] vector
    also inserting next smallest element from [k] arrays to heap*/
    while(!pq.empty()) {
        heap* front = pq.top();
        pq.pop();
        int topData = front->data;
        int topRow = front->rowIndex;
        int topCol = front->colIndex;
        // store the data into [ans] vector
        ans.push_back(topData);
        // now insert another element in heap of the same array to which you've just pushed the data into [ans] vector
        if(topCol+1 < cols) {
            // that means that particular array has some more elements present in it
            heap* new_heap = new heap(given_arrays[topRow][topCol+1], topRow, topCol+1);
            pq.push(new_heap);
        }
    }
}

// merge [k] no. of sorted linked list of same/different size into a single linked list
struct Node {
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};
struct compare {
    bool operator() (Node* first_node, Node* second_node) {
        return first_node->data > second_node->data;
    }
};
Node* merge_k_sorted_lists(vector<Node*> &lists) {
    priority_queue<Node*, vector<Node*>, compare> pq;
    // here we are inserting all the first elements from [k] no. of lists to create a min heap
    for(int i=0; i<lists.size(); ++i) {
        Node* head_list = lists[i];
        if(head_list)
            pq.push(head_list);
    }
    // create a new node in which we re storing the smallest/top element of heap
    Node* head = nullptr;
    Node* tail = nullptr;
    // here we're connecting the top/smallest node from heap to its next smallest node 
    while(!pq.empty()) {
        Node* top_node = pq.top();
        pq.pop();
        if(!head) {
            head = tail = top_node;
            if(top_node->next)
                pq.push(top_node->next);
        }
        else {
            tail->next = top_node;
            tail = top_node;
            if(top_node->next)
                pq.push(top_node->next);
        }
    }
    return head;
}
void insert_at_head(Node* &head, Node* &tail, int data) {
    Node* new_node = new Node(data);
    if(!head)
        head = tail = new_node;
    else {
        tail->next = new_node;
        tail = new_node;
    }
}
// here we're inserting all [k] no. of linked lists in 1D vector
void LinkedList_to_vector(Node* head, vector<Node*> &lists) {
    Node* temp = head;
    while(temp) {
        Node* new_node = new Node(temp->data);
        lists.push_back(new_node);
        temp = temp->next;
    }
}
void print_LL(Node* head) {
    Node* temp = head;
    while(temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// smallest range covering elements from [k] lists/array/vector
vector<int> smallest_range(vector<vector<int>> &nums) {
    priority_queue<heap*, vector<heap*>, custom_comp> pq;
    int maxi = INT_MIN; 
    // here we're processing first [k] elements from each array
    for (int i = 0; i < nums.size(); ++i) {
        heap *temp = new heap(nums[i][0], i, 0);
        pq.push(temp);
        maxi = max(maxi, nums[i][0]);
    }
    // declaring the first ever range here
    int start_range = pq.top()->data;
    int end_range = maxi;
    while (!pq.empty()) {
        heap *top_node = pq.top();
        pq.pop();
        int top_col = top_node->colIndex;
        int top_row = top_node->rowIndex;
        // top most element in heap is the smallest of all that's why it's also the minimum of all
        int mini = top_node->data;
        // here we're comparing tow different ranges for smaller range
        if ((maxi - mini) < (end_range - start_range)) {
            start_range = mini;
            end_range = maxi;
        }
        // here we're inserting a new element in heap, also keeping the track of maximum element
        if (top_col + 1 < nums[top_row].size()) {
            int element = nums[top_row][top_col + 1];
            maxi = max(maxi, element);
            heap *new_heap = new heap(element, top_row, top_col + 1);
            pq.push(new_heap);
        }
        else {
            // if there is no element remaining in any array to push then there is no point in further processing of this program
            break;
        }
    }
    vector<int> ans;
    ans.push_back(start_range);
    ans.push_back(end_range);
    return ans;
}

int main() {

    // int rows, cols;
    // cout << "enter rows and columns : ";
    // cin >> rows >> cols;
    // vector<vector<int>> sorted_arrays(rows, vector<int>(cols));
    // cout << "enter the arrays : " << endl;
    // for(int i=0; i<rows; ++i) {
    //     cout << "enter your " << i+1 << " array here : ";
    //     for(int j=0; j<cols; ++j)
    //         cin >> sorted_arrays[i][j];
    // }
    // vector<int> ans;
    // merege_k_sorted_arrays(ans, rows, cols, sorted_arrays);
    // cout << "here is your merged sorted array : " << endl << "[ ";
    // for(int x:ans)
    //     cout << x << " ";
    // cout << "]" << endl;

    // Node *head, *tail;
    // head = tail = nullptr;
    // int test_case;
    // cout << "enter the no. of linked list you want to create : ";
    // cin >> test_case;
    // vector<Node*> lists;
    // while(test_case--) {
    //     int n, i;
    //     cout << "enter the size of linked list : ";
    //     cin >> n;
    //     for(i=0; i<n; ++i) {
    //         int value;
    //         cin >> value;
    //         insert_at_head(head, tail, value);
    //     }
    //     cout << "here is your linked list : ";
    //     print_LL(head);
    //     LinkedList_to_vector(head, lists);
    //     /*Reset head and tail to nullptr after inserting one linked list into the vector
    //     we're doing this as when the second linked list should insert it shouldn't connected to the same list*/
    //     head = tail = nullptr;
    // }
    // cout << "here is the combined representation of all linked list :" << endl << "[ ";
    // for(Node* num:lists) 
    //     cout << num->data << " ";
    // cout << "]" << endl;
    // Node* ans = merge_k_sorted_lists(lists);
    // cout << "here is your merged linked list : " << endl;
    // print_LL(ans);

    // int rows, cols;
    // cout << "enter rows : ";
    // cin >> rows;
    // vector<vector<int>> nums(rows, vector<int>(cols));
    // for(int i=0; i<rows; ++i) {
    //     cout << "enter your " << i+1 << " array here : " << endl;
    //     cout << "how many elements in this array : ";
    //     cin >> cols;
    //     for(int j=0; j<cols; ++j)
    //         cin >> nums[i][j];
    // }
    // vector<int> ans = smallest_range(nums);
    // cout << "here is your smallest range : " << "[ ";
    // for(int x:ans)
    //     cout << x << " ";
    // cout << "]" << endl;

    return 0;
}