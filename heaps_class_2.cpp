#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(0), right(0) {}
};
Node* create_tree() {
    int data;
    cout << "enter data : ";
    cin >> data;
    if(data == 0)
        return 0;
    Node* root = new Node(data);
    cout << "enter the left data : " << endl;
    root->left = create_tree();
    cout << "enter the right data : " << endl;
    root->right = create_tree();
    return root;
}
void level_order_traversal(Node* root) {
    queue<Node*>q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty()) {
        Node* temp = q.front();q.pop();
        if(!temp) {
            cout << endl;
            if(!q.empty())
                q.push(nullptr);
        }
        else {
            cout << temp->data << " ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    }
}

// given an array in the input, return the kth smallest/largest element
int get_kth_smallest(int arr[], int k, int n) {
    priority_queue<int> pq;
    // step 1: create max heap of [k] elements
    for(int i=0; i<k; ++i) {
        pq.push(arr[i]);
    }
    // step 2: now insert all the remaining elements in the array
    while(k < n) {
        if(arr[k] < pq.top()) {
            pq.pop();
            // after pushing the new element, we've to heapify it also
            pq.push(arr[k++]);
        }
        else
            k++;
    }
    return pq.top();
}
int get_kth_largest(int arr[], int k, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<k; ++i)
        pq.push(arr[i]);
    while(k < n) {
        if(arr[k] > pq.top()) {
            pq.pop();
            pq.push(arr[k++]);
        }
        else 
            k++;
    }
    return pq.top();
}

// given a complete binary tree, verify that the given tree must follow the properties of max heap in it
pair<int, bool> verify_max_heap(Node* root) {
    pair<int, bool> ans;
    // base cases
    if(!root){
        ans.first = INT_MIN;
        ans.second = true;
        return ans;
    }
    if(!root->left && !root->right) {
        ans.first = root->data;
        ans.second = true;
        return ans;
    }
    auto left_ans = verify_max_heap(root->left);
    auto right_ans = verify_max_heap(root->right);
    if(root->data > left_ans.first && root->data > right_ans.first && left_ans.second && right_ans.second) {
        ans.first = root->data;
        ans.second = true;
        return ans;
    }
    else {
        ans.first = max(root->data, max(left_ans.first, right_ans.first));
        ans.second = false;
        return ans;
    }
}

// check whether the given tree is a complete binary tree or not
bool is_completeBinaryTree(Node* root) {
    queue<Node*> q;
    q.push(root);
    bool null_found = false;
    while(!q.empty()) {
        Node* front = q.front();
        q.pop();
        if(!front)
            null_found = true;
        else {
            if(null_found)
                return false;
            q.push(front->left);
            q.push(front->right);
        }
    }
    return true;
}

/* given a tree which has both the properies of a complete binary tree[CBT] or a binary search tree[BST]
we've to convert it into a max heap */
void store_inorder(Node* root, vector<int> &inorder) {
    if(!root)
        return;
    store_inorder(root->left, inorder);
    inorder.push_back(root->data);
    store_inorder(root->right, inorder);
}
void replace_using_postorder(Node* root, vector<int> &inorder, int &i) {
    if(!root)
        return;
    replace_using_postorder(root->left, inorder, i);
    replace_using_postorder(root->right, inorder, i);
    root->data = inorder[i++];
}
void convert_into_heap(Node* root) {
    // step 1: store the nodes of the tree in a vector following inorder traversal
    vector<int> inorder;
    store_inorder(root, inorder);
    // step 2: replace the nodes using pre-order traversal to make a proper heap
    int index = 0; 
    replace_using_postorder(root, inorder, index);
}

int main() {

    // initialization of max heap
    // priority_queue<int> pq;
    // // executing heap
    // // method 1:
    // int n;
    // cout << "enter the size of array : ";
    // cin >> n;
    // int *arr = new int[n];
    // for(int i=0; i<n; ++i) {
    //     cin >> arr[i];
    //     pq.push(arr[i]);
    // }
    // // method 2:
    // // pq.push(12);
    // // pq.push(3);
    // // pq.push(16);
    // // pq.push(8);
    // // pq.push(9);
    // // pq.push(2);
    // // accessing elements in heap
    // // only top element we can access
    // cout << "top element in heap : " << pq.top() << endl;
    // // poping elements in heap
    // pq.pop();
    // cout << "top element in heap : " << pq.top() << endl;
    // // indentifying the size of the heap
    // cout << "size of the heap : " << pq.size() << endl;
    // // identifying if the heap is empty or not
    // if(pq.empty())
    //     cout << "heap is empty" << endl;
    // else    
    //     cout << "heap isn't empty" << endl;

    // initialization of min heap
    // priority_queue<int, vector<int>, greater<int>> pq;
    // // executing heap
    // // method 1:
    // int n;
    // cout << "enter the size of array : ";
    // cin >> n;
    // int *arr = new int[n];
    // for(int i=0; i<n; ++i) {
    //     cin >> arr[i];
    //     pq.push(arr[i]);
    // }
    // // method 2:
    // // pq.push(12);
    // // pq.push(3);
    // // pq.push(16);
    // // pq.push(8);
    // // pq.push(9);
    // // pq.push(2);
    // // accessing elements in heap
    // // only top element we can access
    // cout << "top element in heap : " << pq.top() << endl;
    // // poping elements in heap
    // pq.pop();
    // cout << "top element in heap : " << pq.top() << endl;
    // // indentifying the size of the heap
    // cout << "size of the heap : " << pq.size() << endl;
    // // identifying if the heap is empty or not
    // if(pq.empty())
    //     cout << "heap is empty" << endl;
    // else    
    //     cout << "heap isn't empty" << endl;

    // int n, k;
    // cout << "enter the size of array : ";
    // cin >> n;
    // int *arr = new int[n];
    // for(int i=0; i<n; ++i)
    //     cin >> arr[i];
    // cout << "enter the value of [k] : ";
    // cin >> k;
    // cout << "the kth smallest element is : " << get_kth_smallest(arr, k, n) << endl;
    // cout << "the kth largest element is : " << get_kth_largest(arr, k, n) << endl;

    // Node* root = create_tree();
    // cout << "printing tree structure : " << endl;
    // level_order_traversal(root);
    // pair<int, bool> final_ans = verify_max_heap(root);
    // if(final_ans.second) 
    //     cout << "the given compelete binary tree follows the max heap property :)" << endl;
    // else 
    //     cout << "the given compelete binary tree doesn't follows the max heap property :(" << endl;

    // Node* root = create_tree();
    // cout << "ye rha bhai tera tree" << endl;
    // level_order_traversal(root);
    // if(is_completeBinaryTree(root))
    //     cout << "ha bhai ye complete binary hai" << endl;
    // else 
    //     cout << "nhi bhai ye to kahi se bhi complete binary tree nhi lagra" << endl;

    // Node* root = create_tree();
    // cout << "the tree you've created should look like this..." << endl;
    // level_order_traversal(root);
    // convert_into_heap(root);
    // cout << "after converting this tree to a max heap it should look like this..." << endl;
    // level_order_traversal(root);

    return 0;
}